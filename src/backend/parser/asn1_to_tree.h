/*-------------------------------------------------------------------------
 *
 * asn1_to_tree.h
 *        convert asn1 representation of query to Postgresql tree
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"
#include "nodes/parsenodes.h"
#include "asn1/ASNQuery.h"

#ifndef _ASN1_CONVERTER_H
List           *asn1_to_tree(ASNQuery_t *);
SelectStmt     *convert_select_statement(ASNSelectStmt_t *);
List           *convert_res_target_list(struct targets *);
ResTarget      *convert_res_target_node(ASNResTarget_t *);
#endif
