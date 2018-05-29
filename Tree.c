#include <stdlib.h>
#include <string.h>
#include "Tree.h"

node programStart(node program_head, node routine) {
	node root = (node)malloc(sizeof(struct T_node));
	root->valtype = SEQ;
	root->left = program_head;
	root->right = routine;
	return root;
}

node makeProgramHead(Token id) {
	node head = (node)malloc(sizeof(struct T_node));
	head->valtype = STRING;
	strcpy(head->nodeval.stringval, id.tokenval.stringval);
	head->left = head->right = NULL;
	return head;
}

node makeRoutine(node routine_head, node routine_body) {
	node routine = (node)malloc(sizeof(struct T_node));
	routine->valtype = SEQ;
	routine->left = routine_head;
	routine->right = routine_body;
	return routine;
}

node makeSubRoutine(node routine_head, node routine_body) {
	node sub_routine = (node)malloc(sizeof(struct T_node));
	sub_routine->valtype = SEQ;
	sub_routine->left = routine_head;
	sub_routine->right = routine_body;
	return sub_routine;
}

node makeRoutineHead(node label_part) {
    node routine_head = (node)malloc(sizeof(struct T_node));
    routine_head->valtype = SEQ;
    routine_head->left = NULL;
    routine_head->right = label_part;
    return routine_head;
}

void linkNodes(node n1, node n2) {
    n1->right = n2;
    n2->right = NULL;
    return;
}

node makeEmptyNode() {
    node label_part = (node)malloc(sizeof(struct T_node));
    label_part->valtype = EMPTY;
    label_part->left = NULL;
    label_part->right = NULL;
    return label_part;
}

node makeConstExpr(Token name, node const_value) {
	node const_expr = (node)malloc(sizeof(struct T_node));
	const_expr->valtype = EXPR;
	strcpy(const_expr->nodeval.stringval, name.tokenval.stringval);
	const_expr->left = const_value;
	const_expr->right = NULL;
	return const_expr;
}

node linkConstExprs(node head, Token name, node const_value) {
	node const_expr = (node)malloc(sizeof(struct T_node));
	const_expr->valtype = EXPR;
	strcpy(const_expr->nodeval.stringval, name.tokenval.stringval);
	const_expr->left = const_value;
	const_expr->right = NULL;
	node ptr = head;
	while(ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = const_expr;
	return head;
}

node makeInteger(Token const_int) {
	node const_value = (node)malloc(sizeof(struct T_node));
	const_value->valtype = INTEGER;
	const_value->nodeval.intval = const_int.tokenval.intval;
	const_value->left = const_value->right = NULL;
	return const_value;
}

node makeReal(Token const_real) {
	node const_value = (node)malloc(sizeof(struct T_node));
	const_value->valtype = REAL;
	const_value->nodeval.realval = const_real.tokenval.realval;
	const_value->left = const_value->right = NULL;
	return const_value;
}

node makeChar(Token const_char) {
	node const_value = (node)malloc(sizeof(struct T_node));
	const_value->valtype = CHAR;
	const_value->nodeval.charval = const_char.tokenval.charval;
	const_value->left = const_value->right = NULL;
	return const_value;
}

node makeString(Token const_string) {
	node const_value = (node)malloc(sizeof(struct T_node));
	const_value->valtype = STRING;
	strcpy(const_value->nodeval.stringval, const_string.tokenval.stringval);
	const_value->left = const_value->right = NULL;
	return const_value;
}

node makeSysCon(Token sys_con) {
	node const_value = (node)malloc(sizeof(struct T_node));
	const_value->valtype = SYS_CON;
	switch (sys_con.tokenval.sys)
	{
	case _FALSE:
		const_value->nodeval.intval = 0;
		break;
	case MAXINT:
		const_value->nodeval.intval = 32767;
		break;
	case _TRUE:
		const_value->nodeval.intval = 1;
		break;
	default:
		const_value->nodeval.intval = -1;
		break;
	}
	const_value->left = const_value->right = NULL;
	return const_value;
}

node makeTypeDfn(Token name, node type_decl) {
	node id = makeString(name);
	node type_dfn = (node)malloc(sizeof(struct T_node));
	type_dfn->valtype = EXPR;
	type_dfn->left = id;
	type_dfn->right = type_decl;
	return type_dfn;
}

node makeSysType(Token sys_type) {
	node type = (node)malloc(sizeof(struct T_node));
	type->valtype = TYPE;
	switch (sys_type.tokenval.sys)
	{
	case INTEGER:
		type->nodeval.intval = 1;
		break;
	case REAL:
		type->nodeval.intval = 2;
		break;
	case CHAR:
		type->nodeval.intval = 3;
		break;
	case STRING:
		type->nodeval.intval = 4;
		break;
	default:
		type->nodeval.intval = -1;
		break;
	}
	type->left = type->right = NULL;
	return type;
}

node makeCustomType(Token custom_type) {
	node type = (node)malloc(sizeof(struct T_node));
	type->valtype = TYPE;
	strcpy(type->nodeval.stringval, custom_type.tokenval.stringval);
	type->left = type->right = NULL;
	return type;
}

node makeEnumType(node name_list) {
	name_list->valtype = TYPE;
	return name_list;
}

node linkNameNodes(node head, node name) {
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = name;
	return head;
}

node makeRangeType(node const1, node const2) {
	node type = (node)malloc(sizeof(struct T_node));
	type->valtype = RANGE;
	type->left = const1;
	type->right = const2;
	return type;
}

node makeCustomRangeType(node name1, node name2) {
	node type = (node)malloc(sizeof(struct T_node));
	type->valtype = RANGE;
	type->left = name1;
	type->right = name2;
	return type;
}

node makeArrayType(node range, node element_type) {
	node type = (node)malloc(sizeof(struct T_node));
	type->valtype = TYPE;
	type->nodeval.intval = 5;
	type->left = range;
	type->right = element_type;
	return type;
}

node makeRecordType(node field_list) {
	node type = (node)malloc(sizeof(struct T_node));
	type->valtype = TYPE;
	type->nodeval.intval = 6;
	type->left = type->right = NULL;
	return type;
}

node linkFieldNodes(node head, node field) {
	node ptr = head;
	while(ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = field;
	return head;
}

node makeFieldNode(node field_decl) {
	node field = (node)malloc(sizeof(struct T_node));
	field->valtype = EXPR;
	field->left = field_decl;
	field->right = NULL;
	return field;
}

node makeFieldDecl(node name_list, node type) {
	node field_decl = (node)malloc(sizeof(struct T_node));
	field_decl->valtype = EXPR;
	field_decl->left = name_list;
	field_decl->right = type;
	return field_decl;
}

node linkVarNodes(node head, node var) {
	node ptr = head;
	while(ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = var;
	return head;
}

node makeVarNode(node var_decl) {
	node var = (node)malloc(sizeof(struct T_node));
	var->valtype = EXPR;
	var->left = var_decl;
	var->right = NULL;
	return var;
}

node makeVarDecl(node name_list, node type) {
	node var_decl = (node)malloc(sizeof(struct T_node));
	var_decl.valtype = EXPR;
	var_decl->left = name_list;
	var_decl->right = type;
	return var_decl;
}

