#ifndef TREE_H
#define TREE_H
#include "Token.h"

enum node_type {
	INTEGER,
	REAL,
	CHAR,
	STRING,
	SYS_CON,
	ARRAY,
	RECORD,
	TYPE,
	RANGE,
	OP,
	UNARY_OP,
	EXPR,
	ASSIGN,
	SYS_FUNC,
	FUNC,
	PROC,
	REFERENCE,
	SEQ,
	EMPTY
};

typedef struct T_node *node;
typedef node sub_node;

struct T_node {
	node_type valtype;
	union {
		int intval;
		double realval;
		char charval;
		char stringval[16];
	} nodeval;
	sub_node left;
	sub_node right;
};

node programStart(node program_head, node routine);
node makeProgramHead(Token id);
node makeRoutine(node routine_head, node routine_body);
node makeSubRoutine(node routine_head, node routine_body);

node makeRoutineHead(node label_part);
void linkNodes(node n1, node n2);
node makeEmptyNode();

node makeConstExpr(Token name, node const_value);
node linkConstExprs(node head, Token name, node const_value);

node makeInteger(Token const_int);
node makeReal(Token const_real);
node makeChar(Token const_char);
node makeString(Token const_string);
node makeSysCon(Token sys_con);

node linkTypeDecls(node head, node type_dfn);
node makeTypeDecl(node type_dfn);
node makeTypeDfn(Token name, node type_decl);

node makeSysType(Token sys_type);
node makeCustomType(Token custom_type);
node makeEnumType(node name_list);

node linkNameNodes(node head, node name);

node makeRangeType(node const1, node const2);
node makeCustomRangeType(node name1, node name2);

node makeArrayType(node range, node element_type);

node makeRecordType(node field_list);
node linkFieldNodes(node head, node field);
node makeFieldNode(node field_decl);
node makeFieldDecl(node name_list, node type);

node linkVarNodes(node head, node var);
node makeVarNode(node var_decl);
node makeVarDecl(node name_list, node type);

node makeProcNode(node proc_decl);
node linkProcNodes(node head, node proc_decl);

node makeFuncNode(node func_decl);
node linkFuncNodes(node head, node func_decl);

node makeProcDecl(node head, node sub_routine);
node makeProcHead(Token id, node parameters);

node makeFuncDecl(node head, node sub_routine);
node makeFuncHead(Token id, node parameters, node return_type);

node makeRefVarList(node name_list);
node makeParaDecl(node var_list, node type);
node makeParaNode(node para_decl);
node linkParaNodes(node head, node para_decl);

node binOp1(node operand1, Token oper, node operand2);
node binOp2(node operand1, Token oper, node operand2);
node unaryOp(Token unary_op, node factor);

node callFunct(Token funct, node args_list);
node callSysFunct(Token sys_funct, node args_list);

node makeArrayElement(Token id, node index);
node makeRecdMember(Token recd_id, Token mem_id);

node linkExprs(node head, node expr);
node makeExprNode(node expr);

node simpleVarAssign(Token id, node expr);
node arrayVarAssign(Token array_id, node index, node expr);
node recordVarAssign(Token record_id, Token member, node expr);



#endif
