/*-------------------------------------------------------------------------
 *
 * fe-exec.c
 *	  functions related to sending a query down to the backend
 *
 * Portions Copyright (c) 1996-2012, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/interfaces/libpq/fe-exec.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include <ctype.h>
#include <fcntl.h>

#include "libpq-fe.h"
#include "libpq-int.h"

#include "mb/pg_wchar.h"

extern bool PQsendQueryStart(PGconn *conn);

int		  PQsendASNQuery(PGconn *conn, const char *query);
PGresult *PQASNexec(PGconn *conn, const char *query);
void	  symbol_for_ruby_pg(void);

/*
 * ASN.1 related
 */
#include "nodes/parsenodes.h"
#include "ASNQuery.h"
ASNQuery_t *tree_to_asn1(List *);
List *raw_parser(const char *);
bool PQexecStart(PGconn *conn);
PGresult *PQexecFinish(PGconn *conn);
asn_app_consume_bytes_f consume_bytes;

struct bufferInfo
{
	char	*buffer;
	int		 offset;
	int		 length;
};

int consume_bytes(const void *buffer, size_t size, void *application_specific_key)
{
	struct bufferInfo *bufferInfo = (struct bufferInfo *)application_specific_key;

	memcpy((void *)(bufferInfo->buffer + bufferInfo->offset), buffer, size);

	bufferInfo->offset += size;

	return 0;
}

/*
 * PQsendASNQuery
 *	 Submit a query, ASN.1 encoded, but don't wait for it to finish
 *
 * Returns: 1 if successfully submitted
 *			0 if error (conn->errorMessage is set)
 */
int
PQsendASNQuery(PGconn *conn, const char *query)
{
	int encoding = 0;

	/*
	 * Additional code to support ASN.1 encoding
	 */
	List *l = NULL;

	char buffer[32768];
	asn_enc_rval_t	  ec;
	struct bufferInfo bufferInfo;
	ASNQuery_t	 *queryStmt;

	/* check the argument */
	if (!query)
	{
		printfPQExpBuffer(&conn->errorMessage,
						libpq_gettext("command string is a null pointer\n"));
		return 0;
	}

	l = raw_parser(query);
	queryStmt = tree_to_asn1(l);

	bufferInfo.buffer = buffer;
	bufferInfo.offset = 0;
	bufferInfo.length = 32768;

	if (encoding == 0)
	{
		ec = xer_encode(&asn_DEF_ASNQuery, (void *)queryStmt, XER_F_CANONICAL,
		(asn_app_consume_bytes_f *)consume_bytes, (void *)&bufferInfo);
		if (ec.encoded == -1)
		{
			asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
			return 0;
		}
	}
	else if (encoding == 1)
	{
		ec = der_encode(&asn_DEF_ASNQuery, (void *)queryStmt,
		(asn_app_consume_bytes_f *)consume_bytes, (void *)&bufferInfo);
		if (ec.encoded == -1)
		{
			asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
			return 0;
		}
	}
	else if (encoding == 2)
	{
		ec = uper_encode(&asn_DEF_ASNQuery, (void *)queryStmt,
		(asn_app_consume_bytes_f *)consume_bytes, (void *)&bufferInfo);
		if (ec.encoded == -1)
		{
			asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
			return 0;
		}
	}

	/*
	 * Almost the same PQsendQuery code
	 */
	if (!PQsendQueryStart(conn))
	{
		asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
		return 0;
	}


	/* construct the outgoing Query message */
	if (pqPutMsgStart('A', false, conn) < 0 ||
		pqPutInt(encoding, 4, conn) < 0 || /* Encoding */
		pqPutInt(bufferInfo.offset, 4, conn) < 0 ||
		pqPutnchar(buffer, bufferInfo.offset, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
	{
		asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
		pqHandleSendFailure(conn);
		return 0;
	}

	/* No need to keep the encoded data around anymore */
	asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);

	/* remember we are using simple query protocol */
	conn->queryclass = PGQUERY_SIMPLE;

	/* and remember the query text too, if possible */
	/* if insufficient memory, last_query just winds up NULL */
	if (conn->last_query)
		free(conn->last_query);
	conn->last_query = strdup(query);

	/*
	 * Give the data a push.  In nonblock mode, don't complain if we're unable
	 * to send it all; PQgetResult() will do any additional flushing needed.
	 */
	if (pqFlush(conn) < 0)
	{
		pqHandleSendFailure(conn);
		return 0;
	}

	/* OK, it's launched! */
	conn->asyncStatus = PGASYNC_BUSY;
	return 1;
}

PGresult *
PQASNexec(PGconn *conn, const char *query) 
{
	if (!PQexecStart(conn))
        return NULL;
    if (!PQsendASNQuery(conn, query))
        return NULL;
    return PQexecFinish(conn);
}

void
symbol_for_ruby_pg()
{
	return;
}
