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

/*
 * ASN.1 related
 */
#include "nodes/parsenodes.h"
#include "ASNQuery.h"
#include "pg-asn1-encode.h"

extern bool PQsendQueryStart(PGconn *conn);
extern struct transferBuffer *pg_asn1_encode(List *l, int encoding);
extern void	pg_asn1_buffer_free(struct transferBuffer *transferBuffer);


int		  PQsendASNQuery(PGconn *conn, const char *query);
PGresult *PQASNexec(PGconn *conn, const char *query);
void	  symbol_for_ruby_pg(void);

List	 *raw_parser(const char *);
PGresult *PQexecFinish(PGconn *conn);
bool	  PQexecStart(PGconn *conn);

/*
 * PQsendASNQuery
 *	 Submit a query, ASN.1 encoded, but don't wait for it to finish
 *
 * Returns: 1 if successfully submitted
 *			0 if error (conn->errorMessage is set)
 *
 * NOTES
 * XXXXX - when is it safe to free bufferInfo / buffer?
 */
int
PQsendASNQuery(PGconn *conn, const char *query)
{
	struct transferBuffer *transferBuffer = NULL;
	List *l = NULL;

	int encoding = 0;

	/* check the argument */
	if (!query)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("command string is a null pointer\n"));
		return 0;
	}

	l = raw_parser(query);
	transferBuffer = pg_asn1_encode(l, encoding);

	/*
	 * Almost the same PQsendQuery code
	 */
	if (!PQsendQueryStart(conn))
	{
		pg_asn1_buffer_free(transferBuffer);
		return 0;
	}


	/* construct the outgoing Query message */
	if (pqPutMsgStart('A', false, conn) < 0 ||
		pqPutInt(encoding, 4, conn) < 0 || /* Encoding */
		pqPutInt(transferBuffer->bufferInfo.offset, 4, conn) < 0 ||
		pqPutnchar(transferBuffer->bufferInfo.buffer, transferBuffer->bufferInfo.offset, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
	{
		pg_asn1_buffer_free(transferBuffer);
		pqHandleSendFailure(conn);
		return 0;
	}

	/* No need to keep the encoded data around anymore */
	pg_asn1_buffer_free(transferBuffer);

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
