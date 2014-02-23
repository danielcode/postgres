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
#include "pg-asn1-encode.h"

extern bool		 PQsendQueryStart(PGconn *conn);
extern PGresult *PQexecFinish(PGconn *conn);
extern bool		 PQexecStart(PGconn *conn);


int		  PQsendASNQuery(PGconn *conn, const char *query, const int msglen);
PGresult *PQASNexec(PGconn *conn, const char *query, const int msglen);
void	  symbol_for_ruby_pg(void);


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
PQsendASNQuery(PGconn *conn, const char *query, const int msglen)
{
	int encoding = 1;
	struct bufferInfo bufferInfo;

    bufferInfo.buffer = query;
    bufferInfo.offset = msglen;
    bufferInfo.length = msglen;

	/* check the argument */
	if (!query)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("command string is a null pointer\n"));
		return 0;
	}

	/*
	 * Almost the same PQsendQuery code
	 */
	if (!PQsendQueryStart(conn))
	{
		return 0;
	}


	/* construct the outgoing Query message */
	if (pqPutMsgStart('A', false, conn) < 0 ||
		pqPutInt(encoding, 4, conn) < 0 || /* Encoding */
		pqPutInt(bufferInfo.offset, 4, conn) < 0 ||
		pqPutnchar(bufferInfo.buffer, bufferInfo.offset, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
	{
		pqHandleSendFailure(conn);
		return 0;
	}

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
PQASNexec(PGconn *conn, const char *query, const int msglen)
{
	if (!PQexecStart(conn))
        return NULL;
    if (!PQsendASNQuery(conn, query, msglen))
        return NULL;
    return PQexecFinish(conn);
}

void
symbol_for_ruby_pg()
{
	return;
}
