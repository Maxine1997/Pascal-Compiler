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
	node const_expr = makeConstExpr(name, const_value);
	node ptr = head;
	while (ptr->right != NULL) {
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

node linkTypeDecls(node head, node type_dfn) {
	node type_decl = makeTypeDecl(type_dfn);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = type_decl;
	return head;
}

node makeTypeDecl(node type_dfn) {
	node type_decl = (node)malloc(sizeof(struct T_node));
	type_decl->valtype = EXPR;
	type_decl->left = type_dfn;
	type_decl->right = NULL;
	return type_decl;
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
	node field_node = makeFieldNode(field);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = field_node;
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
	node var_node = makeVarNode(var);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = var_node;
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
	var_decl->valtype = EXPR;
	var_decl->left = name_list;
	var_decl->right = type;
	return var_decl;
}

node makeProcNode(node proc_decl) {
	node proc_node = (node)malloc(sizeof(struct T_node));
	proc_node->valtype = PROC;
	proc_node->left = proc_decl;
	proc_node->right = NULL;
	return proc_node;
}

node linkProcNodes(node head, node proc_decl) {
	node proc = makeProcNode(proc_decl);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = proc;
	return head;
}

node makeFuncNode(node func_decl) {
	node func_node = (node)malloc(sizeof(struct T_node));
	func_node->valtype = FUNC;
	func_node->left = func_decl;
	func_node->right = NULL;
	return func_node;
}

node linkFuncNodes(node head, node func_decl) {
	node func = makeFuncNode(func_decl);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = func;
	return head;
}

node makeProcDecl(node head, node sub_routine) {
	node proc = (node)malloc(sizeof(struct T_node));
	proc->valtype = SEQ;
	proc->left = head;
	proc->right = sub_routine;
	return proc;
}

node makeProcHead(Token id, node parameters) {
	node proc_head = (node)malloc(sizeof(struct T_node));
	proc_head->valtype = SEQ;
	strcpy(proc_head->nodeval.stringval, id.tokenval.stringval);
	proc_head->left = parameters;
	proc_head->right = NULL;
	return proc_head;
}

node makeFuncDecl(node head, node sub_routine) {
	node func = (node)malloc(sizeof(struct T_node));
	func->valtype = SEQ;
	func->left = head;
	func->right = sub_routine;
	return func;
}

node makeFuncHead(Token id, node parameters, node return_type) {
	node func_head = (node)malloc(sizeof(struct T_node));
	func_head->valtype = SEQ;
	strcpy(func_head->nodeval.stringval, id.tokenval.stringval);
	func_head->left = parameters;
	func_head->right = return_type;
	return func_head;
}

node makeRefVarList(node name_list) {
	name_list->valtype = REFERENCE;
	return name_list;
}

node makeParaDecl(node var_list, node type) {
	node para_decl = (node)malloc(sizeof(struct T_node));
	para_decl->valtype = EXPR;
	para_decl->left = var_list;
	para_decl->right = type;
	return para_decl;
}

node makeParaNode(node para_decl) {
	node para = (node)malloc(sizeof(struct T_node));
	para->valtype = EXPR;
	para->left = para_decl;
	para->right = NULL;
	return para;
}

node linkParaNodes(node head, node para_decl) {
	node para = makeParaNode(para_decl);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = para;
	return head;
}

node binOp1(node operand1, Token oper, node operand2) {
	node op = (node)malloc(sizeof(struct T_node));
	op->valtype = OP;
	switch (oper.tokenval.resv) {
	case PLUS:
		op->nodeval.intval = 1;
		break;
	case MINUS:
		op->nodeval.intval = 2;
		break;
	case MUL:
		op->nodeval.intval = 3;
		break;
	case DIV:
		op->nodeval.intval = 4;
		break;
	case MOD:
		op->nodeval.intval = 5;
		break;
	case AND:
		op->nodeval.intval = 6;
		break;
	case OR:
		op->nodeval.intval = 7;
		break;
	default:
		break;
	}
	op->left = operand1;
	op->right = operand2;
	return op;
}

node binOp2(node operand1, Token oper, node operand2) {
	node op = (node)malloc(sizeof(struct T_node));
	op->valtype = OP;
	switch (oper.tokenval.deli) {
	case GE:
		op->nodeval.intval = 1;
		break;
	case GT:
		op->nodeval.intval = 2;
		break;
	case LE:
		op->nodeval.intval = 3;
		break;
	case LT:
		op->nodeval.intval = 4;
		break;
	case EQUAL:
		op->nodeval.intval = 5;
		break;
	case UNEQUAL:
		op->nodeval.intval = 6;
		break;
	default:
		break;
	}
	op->left = operand1;
	op->right = operand2;
	return op;
}

node unaryOp(Token unary_op, node factor) {
	node op = (node)malloc(sizeof(struct T_node));
	op->valtype = UNARY_OP;
	switch (unary_op.tokenval.resv) {
	case MINUS:
		op->nodeval.intval = 1;
		break;
	case NOT:
		op->nodeval.intval = 2;
		break;
	default:
		break;
	}
	op->left = factor;
	op->right = NULL;
	return op;
}

node callFunct(Token funct, node args_list) {
	node call_funct = (node)malloc(sizeof(struct T_node));
	call_funct->valtype = FUNC;
	strcpy(call_funct->nodeval.stringval, funct.tokenval.stringval);
	call_funct->left = args_list;
	call_funct->right = NULL;
	return call_funct;
}

node callSysFunct(Token sys_funct, node args_list) {
	node call_funct = (node)malloc(sizeof(struct T_node));
	call_funct->valtype = SYS_FUNC;
	strcpy(call_funct->nodeval.stringval, sys_funct.tokenval.stringval);
	call_funct->left = args_list;
	call_funct->right = NULL;
	return call_funct;
}

node makeArrayElement(Token id, node index) {
	node element = (node)malloc(sizeof(struct T_node));
	element->valtype = ARRAY;
	strcpy(element->nodeval.stringval, id.tokenval.stringval);
	element->left = index;
	element->right = NULL;
	return element;
}

node makeRecdMember(Token recd_id, Token mem_id) {
	node member = (node)malloc(sizeof(struct T_node));
	member->valtype = STRING;
	strcpy(member->nodeval.stringval, mem_id.tokenval.stringval);
	member->left = member->right = NULL;
	node record = (node)malloc(sizeof(struct T_node));
	record->valtype = RECORD;
	strcpy(record->nodeval.stringval, recd_id.tokenval.stringval);
	record->left = member;
	record->right = NULL;
	return record;
}

node linkExprs(node head, node expr) {
	node expr_node = makeExprNode(expr);
	node ptr = head;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	ptr->right = expr_node;
	return head;
}

node makeExprNode(node expr) {
	node expr_node = (node)malloc(sizeof(struct T_node));
	expr_node->valtype = EXPR;
	expr_node->left = expr;
	expr_node->right = NULL;
	return expr_node;
}

node simpleVarAssign(Token id, node expr) {
	node simple_var = makeString(id);
	node stmt = (node)malloc(sizeof(struct T_node));
	stmt->valtype = ASSIGN;
	stmt->left = simple_var;
	stmt->right = expr;
	return stmt;
}

node arrayVarAssign(Token array_id, node index, node expr) {
	node array_var = makeArrayElement(array_id, index);
	node stmt = (node)malloc(sizeof(struct T_node));
	stmt->valtype = ASSIGN;
	stmt->left = array_var;
	stmt->right = expr;
	return stmt;
}

node recordVarAssign(Token record_id, Token member, node expr) {
	node record_var = makeRecdMember(record_id, member);
	node stmt = (node)malloc(sizeof(struct T_node));
	stmt->valtype = ASSIGN;
	stmt->left = record_var;
	stmt->right = expr;
	return stmt;
}

