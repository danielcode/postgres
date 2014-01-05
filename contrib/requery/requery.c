/*-------------------------------------------------------------------------
 *
 * requery.c
 *	  Extension to support testing of node -> SQL code and transfer
 *        decoding
 *
 * Copyright (c) 2013, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *	  contrib/requery/requery.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"
#include "fmgr.h"
#include "executor/spi.h"
#include "lib/stringinfo.h"

PG_MODULE_MAGIC;


/*
 * types
 */

/*
 * prototypes
 */
PG_FUNCTION_INFO_V1(requery);
Datum	requery(PG_FUNCTION_ARGS);

/*
 * functions
 */
Datum
requery(PG_FUNCTION_ARGS)
{
	StringInfoData sid;
	int ret, proc;

	/* PG_RETURN_POINTER(pst); */
	const char *string = PG_GETARG_CSTRING(0);

	/* Connect to SPI manager */
	if ((ret = SPI_connect()) < 0)
	{
		/* internal error */
		elog(ERROR, "crosstab: SPI_connect returned %d", ret);
	}

	ret  = SPI_transfer_execute(string, false, 0);
    proc = SPI_processed;

	/* If no qualifying tuples, fall out early */
	if (!(ret == SPI_OK_SELECT 			 ||
		  ret == SPI_OK_INSERT_RETURNING ||
		  ret == SPI_OK_DELETE_RETURNING ||
		  ret == SPI_OK_UPDATE_RETURNING ||
		  proc <= 0))
	{
		SPI_finish();
		/* rsinfo->isDone = ExprEndResult; */
		/* PG_RETURN_NULL(); */
		PG_RETURN_CSTRING(string);
	}






	if (ret > 0 && SPI_tuptable != NULL)
	{
		int i, j;
		TupleDesc	   tupdesc  = SPI_tuptable->tupdesc;
		SPITupleTable *tuptable = SPI_tuptable;

		initStringInfo(&sid);

		for (j = 0; j < proc; j++)
		{
			HeapTuple tuple = tuptable->vals[j];

			for (i = 1; i <= tupdesc->natts; i++)
			{
				appendStringInfo(&sid, " %s%s", SPI_getvalue(tuple, tupdesc, i), (i == tupdesc->natts) ? " " : " |");
			}

			elog(INFO, "EXECQ: %s", sid.data);
		}

		
	}








	SPI_finish();

	PG_RETURN_CSTRING(sid.data);
}
