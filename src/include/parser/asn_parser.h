/*-------------------------------------------------------------------------
 *
 * parser.h
 *		Definitions for the "raw" parser (flex and bison phases only)
 *
 * This is the external API for the raw lexing/parsing functions.
 *
 * Portions Copyright (c) 1996-2012, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/parser/parser.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef ASN_PARSER_H
#define ASN_PARSER_H

#include "nodes/parsenodes.h"

/* Primary entry point for the raw asn parsing functions */
extern List *raw_asn_parser(const char *str, int msglen);
extern void  symbol_for_ruby_pg(void);

#endif   /* PARSER_H */
