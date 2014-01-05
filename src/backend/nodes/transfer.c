/*-------------------------------------------------------------------------
 *
 * transfer.c
 *        Interface to convert to / from transfer syntax
 *
 *
 * Copyright (c) 2013, Daniel Harris
 *
 * src/backend/nodes/transfer.c
 *   
 *-------------------------------------------------------------------------
 */

#include "postgres.h"
#include "nodes/nodes.h"

/*
 * toTransferSyntax
 * 	    Convert nodes representing SQL expression to transfer syntax.
 */
void *
toTransferSyntax(const void *obj)
{
	return NULL;
}


/*
 * fromTransferSyntax
 * 	    Convert transfer syntax to nodes.
 */
void *
fromTransferSyntax(const void *obj)
{
	return NULL;
}
