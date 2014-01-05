/*-------------------------------------------------------------------------
 *
 * toSQL.c
 *        Convert Node tree to SQL
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
#include "nodes/parsenodes.h"
/* #include "nodes/pg_list.h" */

#include "lib/stringinfo.h"

/*
 * Prototypes
 */
char *toSQL(const void *obj);
void  nodesToSQL(StringInfo sqlString, Node *node);
void  selectStmtToSQL(StringInfo sqlString, Node *node);
void  selectStmtListToSQL(StringInfo sqlString, Node *node);
void  resTargetListToSQL(StringInfo sqlString, Node *node);
void  resTargetToSQL(StringInfo sqlString, Node *node);
void  expressionToSQL(StringInfo sqlString, Node *node);
void  valueStringToSQL(StringInfo sqlString, Node *node);
void  valueFloatToSQL(StringInfo sqlString, Node *node);
void  valueIntegerToSQL(StringInfo sqlString, Node *node);


/*
 * toSQL
 * 	    Convert nodes to SQL
 */
char *
toSQL(const void *obj)
{

	/*
	 * Check that node is top-level SQL statement
	 */

	/*
	 * Initialize memory
	 */
	StringInfo sqlString = makeStringInfo();

	selectStmtListToSQL(sqlString, (Node *)obj);
	appendStringInfo(sqlString, " ;");

	return sqlString->data;
}

void
nodesToSQL(StringInfo sqlString, Node *node)
{
	switch(node->type)
	{
		case T_List :
			selectStmtListToSQL(sqlString, node);
			
		case T_SelectStmt :
			selectStmtToSQL(sqlString, node);
			break;

		default :
			break;
	}

	return;
}

void
selectStmtToSQL(StringInfo sqlString, Node *node)
{
	SelectStmt *ss = (SelectStmt *)node;

	appendStringInfo(sqlString, "SELECT ");

	/*
	 * Select targets
	 */
	if (ss->targetList != NIL)
	{
		ListCell *lc = ss->targetList->head;

		while (lc != (ListCell *)NULL)
		{
			Node *resTarget = lc->data.ptr_value;

			resTargetToSQL(sqlString, resTarget);

			lc = lc->next;
		}
	}

	/*
	 * FROM clause
	 */

	/* Incomplete! */
	
	return;
}

void
selectStmtListToSQL(StringInfo sqlString, Node *node)
{
	/*
	 * For the moment cheat, and assume only one select statement.
	 */
	List *list		 = (List *)node;
	Node *selectNode = linitial(list);
	selectStmtToSQL(sqlString, selectNode);
}

void
resTargetListToSQL(StringInfo sqlString, Node *node)
{
	ResTarget *rt		   = (ResTarget *)node;
	int		   valNodeType = nodeTag(node);

	if (valNodeType == T_ColumnRef)
	{
	  if (rt->name)
	  {
	  }
	}
	else
	{
	}
}

void
resTargetToSQL(StringInfo sqlString, Node *node)
{
	ResTarget *rt		    = (ResTarget *)node;
	Node	  *resTargetVal = rt->val;
	int		   valNodeType  = nodeTag(resTargetVal);

	if (valNodeType == T_ColumnRef)
	{
		ColumnRef *cr	   = (ColumnRef *)resTargetVal;
		Node	  *valNode = linitial(cr->fields);

		if (valNode->type == T_A_Star)
		{
			appendStringInfo(sqlString, " * ");
		}
		else if (valNode->type == T_String)
		{
			Value *v = (Value *)valNode;
			appendStringInfo(sqlString, " %s ", v->val.str);
		}

		if (rt->name)
		{
			appendStringInfo(sqlString, " AS %s ", rt->name);
		}
	}
	else
	{
		expressionToSQL(sqlString, rt->val);

		if (rt->name)
		{
			appendStringInfo(sqlString, " AS %s ", rt->name);
		}
	}
}

void
expressionToSQL(StringInfo sqlString, Node *node)
{
	int nodeType = node->type;

	if (nodeType == T_A_Const) {
		A_Const *ac = (A_Const *)node;

		switch(ac->val.type)
		{
			case T_Integer :
				valueIntegerToSQL(sqlString, (Node *)&ac->val);
				break;

			case T_String  :
				valueStringToSQL(sqlString, (Node *)&ac->val);
				break;

			case T_Float   :
				valueFloatToSQL(sqlString, (Node *)&ac->val);
				break;

			default :
				appendStringInfo(sqlString, " 'UNPROCESSED CONSTANT' ");
				break;
		}
	}
	else
	{
		appendStringInfo(sqlString, " 'UNPROCESSED CONSTANT' ");
	}
}

void
valueStringToSQL(StringInfo sqlString, Node *node)
{
	Value *v = (Value *)node;

	appendStringInfo(sqlString, "'%s'", v->val.str);
}

void
valueFloatToSQL(StringInfo sqlString, Node *node)
{
	Value *v = (Value *)node;

	appendStringInfo(sqlString, "%s", v->val.str);
}

void
valueIntegerToSQL(StringInfo sqlString, Node *node)
{
	Value *v = (Value *)node;

	appendStringInfo(sqlString, "%ld", v->val.ival);
}
