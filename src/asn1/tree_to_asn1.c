#include "postgres.h"
#include "nodes/parsenodes.h"
#include "ASNQuery.h"

ASNQuery_t		*tree_to_asn1(List *l);
ASNSelectStmt_t	*select_statement_to_asn1(SelectStmt *ss);
ASNResTarget_t	*res_target_to_asn1(ResTarget *rt);
ASNExpression_t	*expr_to_asn1(ASNExpression_t *expr, Node *val);

ASNQuery_t *
tree_to_asn1(List *l)
{
	if (l != NIL)
	{
		ASNQuery_t	*asnQuery	= calloc(1, sizeof(ASNQuery_t));
		ListCell 	*lc			= l->head;

		while (lc != (ListCell *)NULL)
		{
			SelectStmt		*ss	 = (SelectStmt *)lc->data.ptr_value;
			ASNSelectStmt_t	*ass = select_statement_to_asn1(ss);

			asn_sequence_add(&asnQuery->list, ass);

			lc = lc->next;
		}

		return asnQuery;
	}

	return NULL;
}

ASNSelectStmt_t *
select_statement_to_asn1(SelectStmt *ss)
{
	ASNSelectStmt_t	*asnSelectStmt	= calloc(1, sizeof(ASNSelectStmt_t));

	if (ss->targetList != NIL)
	{
		ListCell *lc = ss->targetList->head;

		while (lc != (ListCell *)NULL)
		{
			ResTarget		*rt	 = (ResTarget *)lc->data.ptr_value;
			ASNResTarget_t	*art = res_target_to_asn1(rt);

			asn_sequence_add(&asnSelectStmt->targets.list, art);

			lc = lc->next;
		}
	}

	if (ss->fromClause != NULL)
	{
		struct fromClause *fc = calloc(1, sizeof(struct fromClause));
		ListCell		  *lc = ss->fromClause->head;

		while (lc != (ListCell *)NULL)
		{
			ASNFromClause_t	*afc = calloc(1, sizeof(ASNFromClause_t));
			RangeVar		*rv  = (RangeVar *)lc->data.ptr_value;
			ASNRangeVar_t	*arv = calloc(1, sizeof(ASNRangeVar_t));

			if (rv->catalogname)
			{
				ASNString_t *s = calloc(1, sizeof(ASNString_t));

				s->present = ASNString_PR_asciiString;
				s->choice.asciiString.buf  = (uint8_t *)strdup(rv->catalogname);
				s->choice.asciiString.size = strlen(rv->catalogname);

				arv->catalogName = s;
			}
			else
			{
				arv->catalogName = NULL;
			}

			if (rv->schemaname)
			{
				ASNString_t *s = calloc(1, sizeof(ASNString_t));

				s->present = ASNString_PR_asciiString;
				s->choice.asciiString.buf  = (uint8_t *)strdup(rv->schemaname);
				s->choice.asciiString.size = strlen(rv->schemaname);

				arv->schemaName = s;
			}
			else
			{
				arv->schemaName = NULL;
			}

			/* Code suggests this must be present */
			if (rv->relname)
			{
				ASNString_t *s = calloc(1, sizeof(ASNString_t));

				s->present = ASNString_PR_asciiString;
				s->choice.asciiString.buf  = (uint8_t *)strdup(rv->relname);
				s->choice.asciiString.size = strlen(rv->relname);

				arv->relName = s;
			}
			else
			{
				arv->relName = NULL;
			}

			
			asn_sequence_add(&afc->list, arv);
			asn_sequence_add(&fc->list, afc);

			lc = lc->next;
		}

		asnSelectStmt->fromClause = fc;
	}
	else
	{
		asnSelectStmt->fromClause = NULL;
	}

	return asnSelectStmt;
}

ASNResTarget_t *
res_target_to_asn1(ResTarget *rt)
{
	Node			*resTargetVal = NULL;
	ASNResTarget_t	*asnResTarget = calloc(1, sizeof(ASNResTarget_t));

	int	valNodeType;

	resTargetVal = (Node *)rt->val;
	valNodeType	 = nodeTag(resTargetVal);

	if (valNodeType == T_ColumnRef)
	{
		ColumnRef *cr	   = (ColumnRef *)resTargetVal;
		Node	  *valNode = linitial(cr->fields);
		int		   valType = nodeTag(valNode);

		if (valType == T_A_Star)
		{
			asnResTarget->present = ASNResTarget_PR_star;
		}
		else if (valType == T_String)
		{
			Value *v = (Value *)valNode;

			ASNColumnRefItem_t *columnItem = calloc(1, sizeof(ASNColumnRefItem_t));

			columnItem->present = ASNColumnRefItem_PR_str;
			columnItem->choice.str.present = ASNString_PR_asciiString;
			columnItem->choice.str.choice.asciiString.buf  = (uint8_t *)strdup(v->val.str);
			columnItem->choice.str.choice.asciiString.size = strlen(v->val.str);
			asnResTarget->present = ASNResTarget_PR_columnRef;
			asn_sequence_add(&asnResTarget->choice.columnRef.fields.list, columnItem);
		}
	}
	else
	{
		asnResTarget->present = ASNResTarget_PR_resTargetExpression;
		expr_to_asn1(&asnResTarget->choice.resTargetExpression.expr, rt->val);
	}

	/*
	 * Process name of this target
	 */
	if (rt->name)
	{
		ASNString_t	*columnName	= calloc(1, sizeof(ASNString_t));

		columnName->present = ASNString_PR_asciiString;
		columnName->choice.asciiString.buf	= (uint8_t *)strdup(rt->name);
		columnName->choice.asciiString.size	= strlen(rt->name);

		asnResTarget->choice.resTargetExpression.colLabel = columnName;
	}

	return asnResTarget;
}

ASNExpression_t *
expr_to_asn1(ASNExpression_t *expr, Node *val)
{
	int nt = nodeTag(val);

	if (expr == NULL)
	{
		expr = calloc(1, sizeof(ASNExpression_t));
	}

	/* If we're here, we have an expression. */

	if (nt == T_A_Const)
	{
		A_Const *ac		  = (A_Const *)val;
		int		 const_nt = ac->val.type;
		double	 d;

		switch(const_nt)
		{
			case T_Integer :
				expr->present			= ASNExpression_PR_intConst;
				expr->choice.intConst	= ac->val.val.ival;

				break;

			case T_String :
				expr->present									 = ASNExpression_PR_stringConst;
				expr->choice.stringConst.present				 = ASNString_PR_asciiString;
				expr->choice.stringConst.choice.asciiString.buf	 = (uint8_t *)strdup(ac->val.val.str);
				expr->choice.stringConst.choice.asciiString.size = strlen(ac->val.val.str);

				break;

			case T_Float :
				d = strtod(ac->val.val.str, NULL);

				expr->present			= ASNExpression_PR_floatConst;
				expr->choice.floatConst	= d;

				break;

			default :
				break;
		}
	}
	else if (nt == T_A_Expr)
	{
		ASNBinaryExpression_t *asnBinaryExpression = calloc(1, sizeof(ASNBinaryExpression_t));
		A_Expr	 *ae = (A_Expr *)val;

		expr->present = ASNExpression_PR_binaryExpr;

		if (ae->kind == AEXPR_OP)
		{
			ListCell *lc = ae->name->head;
			Value	 *v  = (Value *)lc->data.ptr_value;
			char	 *op = v->val.str;
			char	  c = op[0];

			expr->present = ASNExpression_PR_binaryExpr;

			if (c == '+')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_plus;
			}
			else if (c == '-')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_minus;
			}
			else if (c == '*')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_multiply;
			}
			else if (c == '/')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_divide;
			}
			else if (c == '%')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_mod;
			}
			else if (c == '^')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_raise;
			}
			else if (c == '<')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_lt;
			}
			else if (c == '>')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_gt;
			}
			else if (c == '=')
			{
				asnBinaryExpression->operator = ASNBinaryOperator_equal;
			}
			else
			{
			}

			asnBinaryExpression->lhs = (struct ASNExpression *)expr_to_asn1(NULL, ae->lexpr);
			asnBinaryExpression->rhs = (struct ASNExpression *)expr_to_asn1(NULL, ae->rexpr);
		}
		else if (ae->kind == AEXPR_AND)
		{
			asnBinaryExpression->operator = ASNBinaryOperator_and;
			asnBinaryExpression->lhs = (struct ASNExpression *)expr_to_asn1(NULL, ae->lexpr);
			asnBinaryExpression->rhs = (struct ASNExpression *)expr_to_asn1(NULL, ae->rexpr);
		}
		else if (ae->kind == AEXPR_OR)
		{
			asnBinaryExpression->operator = ASNBinaryOperator_and;
			asnBinaryExpression->lhs = (struct ASNExpression *)expr_to_asn1(NULL, ae->lexpr);
			asnBinaryExpression->rhs = (struct ASNExpression *)expr_to_asn1(NULL, ae->rexpr);
		}
		else
		{
		}

		expr->choice.binaryExpr = asnBinaryExpression;
	}

	return expr;
}
