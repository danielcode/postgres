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
#include "asn1/per_decoder.h"

#include <stdarg.h>

/**************************************************************************/
/* Prototypes                                                             */
/**************************************************************************/
List		*raw_asn_parser(int encoding, const char *str, int msglen);
List		*asn1_to_tree(ASNQuery_t *query);
List		*convert_from_clauses(struct fromClause *fromClause);
RangeVar	*convert_from_clause(ASNFromClause_t *afc);
SelectStmt	*convert_select_statement(ASNSelectStmt_t *selectStmt);
List		*convert_res_target_list(struct targets *resTargetList);
ResTarget	*convert_res_target_node(ASNResTarget_t *resTarget); 
Node		*convert_expr(ASNExpression_t *expr);
Node		*convert_binary_expression(ASNBinaryExpression_t *be);

extern Node *asn1ToIntConst(ASNExpression_t *expr);
extern Node *asn1ToFloatConst(ASNExpression_t *expr);
extern Node *asn1ToStringConst(ASNExpression_t *expr);


/*
 * raw_asn_paser
 * Top-level entry point taking an encoded byte stream and converting it to a Postgresql List *;
 * the internal representation of a query.
 */
List *
raw_asn_parser(int encoding, const char *str, int msglen)
{
	List *expr = NIL;

	ASNQuery_t              *queryStmt      = NULL;
	asn_dec_rval_t   rval;

	/*
	 * Decode byte stream
	 */
	if (encoding == 0)
	{
		rval = xer_decode(0, &asn_DEF_ASNQuery, (void **)&queryStmt, str, msglen);
		if (rval.code != RC_OK)
		{
			asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
			return NIL;
		}
	}
	else if (encoding == 1)
	{
		rval = asn_DEF_ASNQuery.ber_decoder(0, &asn_DEF_ASNQuery, (void **)&queryStmt, str, msglen, 0);
		if (rval.code != RC_OK)
		{
			asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
			return NIL;
		}
	}
	else if (encoding == 2)
	{
		asn_codec_ctx_t *opt_codec_ctx = 0;

		rval = uper_decode(opt_codec_ctx, &asn_DEF_ASNQuery, (void **)&queryStmt, str, msglen, 0, 0);
		if (rval.code != RC_OK)
		{
			asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);
			return NIL;
		}
	}

	/*
	 * Convert from ASN.1 compiler produced structure to Postgresql query.
	 */
	expr = asn1_to_tree(queryStmt);

	/*
	 * Clean up
	 */
	asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, queryStmt, 0);

	return expr;
}


List *
asn1_to_tree(ASNQuery_t *query)
{
	SelectStmt	*ss		 = convert_select_statement(query->list.array[0]);
	List		*tmpList = lcons(ss, NIL);

	return tmpList;
}


SelectStmt *
convert_select_statement(ASNSelectStmt_t *selectStmt)
{
	SelectStmt *ss;
	ss					= (SelectStmt *)makeNode(SelectStmt);
	ss->distinctClause	= NULL;
	ss->targetList		= convert_res_target_list(&selectStmt->targets);
	ss->intoClause		= NULL;
	ss->fromClause		= convert_from_clauses(selectStmt->fromClause);
	ss->whereClause		= NULL;
	ss->groupClause		= NULL;
	ss->havingClause	= NULL;
	ss->windowClause	= NULL;

	return ss;
}

List *
convert_from_clauses(struct fromClause *fromClause)
{
	List *clauseList = NIL;
	int	  i;

	if (fromClause && fromClause->list.count > 0)
	{
		for (i = 0; i < fromClause->list.count; i++)
		{
			RangeVar *rv = convert_from_clause(fromClause->list.array[i]);
			clauseList = lappend(clauseList, rv);
		}
	}

	return clauseList;
	
}

RangeVar *
convert_from_clause(ASNFromClause_t *afc)
{
	ASNRangeVar_t	*arv = NULL;
	RangeVar 		*rv	 = NULL;

	if (afc->list.count != 1)
	{
		return NULL; /* Error */
	}

	arv = afc->list.array[0];

	rv = makeRangeVar(NULL, strdup((char *)arv->relName->choice.asciiString.buf), 0);

	return rv;
}

List *
convert_res_target_list(struct targets *resTargetList)
{
	List	*resList = NIL;
	int		 i;

	if (resTargetList && resTargetList->list.count > 0)
	{
		for (i = 0; i < resTargetList->list.count; i++)
		{
			ResTarget *tmpRT = convert_res_target_node(resTargetList->list.array[i]);
			resList = lappend(resList, tmpRT);
		}
	}

	return resList;
}


ResTarget *
convert_res_target_node(ASNResTarget_t *resTarget)
{
	ResTarget *resTargetNode = NULL;
	Node *n = NULL;

	if (resTarget)
	{
		resTargetNode = (ResTarget *)makeNode(ResTarget);

		switch(resTarget->present)
		{
			ColumnRef			*cr	 = NULL;
			ASNColumnRef_t		*acr = NULL;
			ASNColumnRefList_t	*crl = NULL;
			ASNColumnRefItem_t	*cri = NULL;

			case ASNResTarget_PR_resTargetExpression :
				n = convert_expr(&resTarget->choice.resTargetExpression.expr);
				break;

			case ASNResTarget_PR_star :
				/* Copied from gram.y */
				cr 			 = (ColumnRef *)makeNode(ColumnRef);
				cr->fields   = list_make1(makeNode(A_Star));
				cr->location = 0;
				n      		 = (Node *)cr;

				break;

			case ASNResTarget_PR_columnRef :
				acr	= &resTarget->choice.columnRef;
				crl = &acr->fields;
				cri = crl->list.array[0];

				if (cri->present == ASNColumnRefItem_PR_str)
				{
					cr = (ColumnRef *)makeNode(ColumnRef);
					cr->fields	 = list_make1(makeString(strdup((char *)cri->choice.str.choice.asciiString.buf)));
					cr->location = 0;

					n = (Node *)cr;
				}
				break;

			default :
				break;
		}

		resTargetNode->name			= NULL;
		resTargetNode->indirection	= NULL;
		resTargetNode->val			= n;
		resTargetNode->location		= 0;

		if (resTarget->choice.resTargetExpression.colLabel)
		{
			resTargetNode->name	= strdup((char *)resTarget->choice.resTargetExpression.colLabel->choice.asciiString.buf);
		}
	}

	return resTargetNode;
}

Node *
convert_expr(ASNExpression_t *expr)
{
	Node	*exprNode	= NULL;

	switch(expr->present)
	{
		case ASNExpression_PR_intConst :
			exprNode = asn1ToIntConst(expr);
			break;

		case ASNExpression_PR_floatConst :
			exprNode = asn1ToFloatConst(expr);
			break;

		case ASNExpression_PR_stringConst :
			exprNode = asn1ToStringConst(expr);
			break;

		case ASNExpression_PR_binaryExpr :
			exprNode = convert_binary_expression(expr->choice.binaryExpr);
			break;

		default :
			break;
	}

	return exprNode;
}

Node *
convert_binary_expression(ASNBinaryExpression_t *be)
{
	Node *operation = NULL;
	Node *lhs		= convert_expr(be->lhs);
	Node *rhs		= convert_expr(be->rhs);

	switch(be->operator)
	{
 		case ASNBinaryOperator_plus :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "+", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_minus :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "-", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_multiply :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "*", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_divide :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "/", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_mod :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "%", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_raise :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "^", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_lt :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "<", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_gt :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, ">", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_equal :
			operation = (Node *)makeSimpleA_Expr(AEXPR_OP, "=", lhs, rhs, 0);
			break;

        case ASNBinaryOperator_and :
			operation = (Node *)makeA_Expr(AEXPR_AND, NIL, lhs, rhs, 0);
			break;

        case ASNBinaryOperator_or :
			operation = (Node *)makeA_Expr(AEXPR_OR, NIL, lhs, rhs, 0);
			break;
	}

	return operation;
}
