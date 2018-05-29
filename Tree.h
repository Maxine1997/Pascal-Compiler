#ifndef TREE_H
#define TREE_H
#include "Token.h"

enum node_type{
	INTEGER,
	REAL,
	CHAR,
	STRING,
	SYS_CON,
	TYPE,
	EXPR,
	RANGE,
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

#endif