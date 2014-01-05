/*-------------------------------------------------------------------------
 *
 * asn1_to_tree.c
 *        convert ASN.1 representation of query to Postgresql tree
 *
 *-------------------------------------------------------------------------
 */

/**************************************************************************/
/* Include Files                                                          */
/**************************************************************************/
#include "postgres.h"
#include "parser/gramparse.h"
#include "parser/parser.h"

#include "nodes/makefuncs.h"

#include "asn1_to_tree.h"
#include "asn1/ASNQuery.h"

#include <stdarg.h>

/**************************************************************************/
/* Prototypes                                                             */
/**************************************************************************/
Node *asn1ToIntConst(ASNExpression_t *expr);
Node *asn1ToFloatConst(ASNExpression_t *expr);
Node *asn1ToStringConst(ASNExpression_t *expr);


Node *
asn1ToIntConst(ASNExpression_t *expr)
{
	A_Const *cnst = makeNode(A_Const);

	cnst->val.type		= T_Integer;
	cnst->val.val.ival	= expr->choice.intConst;
	cnst->location		= 0;

	return (Node *)cnst;
}

Node *
asn1ToFloatConst(ASNExpression_t *expr)
{
	char	*floatStr = NULL;
	A_Const	*cnst     = makeNode(A_Const);

	floatStr = (char *)palloc(64);
	snprintf(floatStr, 63, "%lf", expr->choice.floatConst);

	cnst->val.type		= T_Float;
	cnst->val.val.str	= floatStr;
	cnst->location		= 0;

	return (Node *)cnst;
}

Node *
asn1ToStringConst(ASNExpression_t *expr)
{
	A_Const *cnst = makeNode(A_Const);

	cnst->val.type		= T_String;
	cnst->val.val.str	= strdup((char *)expr->choice.stringConst.choice.asciiString.buf);
	cnst->location		= 0;
			
	return (Node *)cnst;
}
