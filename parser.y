%{
#include "Tree.h"

#define YYSTYPE node

%}

%token PROGRAM _BEGIN END CASE ASSIGN GOTO
%token EQUAL UNEQUAL GE GT LE LT
%token CONST TYPE NAME ARRAY
%token INTEGER REAL CHAR STRING
%token SYS_CON SYS_FUNCT SYS_PROC SYS_TYPE

%%

program: program_head routine DOT       { $$ = programStart($1, $2); };
program_head: PROGRAM ID SEMI           { $$ = makeProgramHead($2); };
routine: routine_head routine_body      { $$ = makeRoutine($1, $2); };
sub_routine: routine_head routine_body  { $$ = makeSubRoutine($1, $2); };
routine_head: label_part const_part type_part var_part routine_part
                                        { $$ = makeRoutineHead($1);
                                          linkNodes($1, $2);
                                          linkNodes($2, $3);
                                          linkNodes($3, $4);
                                          linkNodes($4, $5); };
label_part:                             { $$ = makeEmptyNode(); };
const_part: CONST const_expr_list       { $$ = $2; }
          |                             { $$ = makeEmptyNode(); };
const_expr_list: const_expr_list NAME EQUAL const_value SEMI    { $$ = linkConstExprs($1, $2, $4); }
               | NAME EQUAL const_value SEMI                    { $$ = makeConstExpr($1, $3); };
const_value: INTEGER                    { $$ = makeInteger($1); }
           | REAL                       { $$ = makeReal($1); }
           | CHAR                       { $$ = makeChar($1); }
           | STRING                     { $$ = makeString($1); }
           | SYS_CON                    { $$ = makeSysCon($1); };

type_part: TYPE type_decl_list          { $$ = $2; }
           |                            { $$ = makeEmptyNode(); };
type_decl_list: type_decl_list type_definition                  { $$ = linkTypeDecls($1, $2); }
                | type_definition                               { $$ = makeTypeDecl($1); };
type_definition: NAME EQUAL type_decl SEMI                      { $$ = makeTypeDfn($1, $3); };
type_decl: simple_type_decl             { $$ = $1; }
         | array_type_decl              { $$ = $1; }
         | record_type_decl             { $$ = $1; };
simple_type_decl: SYS_TYPE                                      { $$ = makeSysType($1); }
                | NAME                                          { $$ = makeCustomType($1); }
                | LP name_list RP                               { $$ = makeEnumType($2); }
                | const_value DOTDOT const_value                { $$ = makeRangeType($1, $3); }
//              | MINUS const_value DOTDOT const_value          {}
//              | MINUS const_value DOTDOT MINUS const_value    {}
                | NAME DOTDOT NAME                              { $$ = makeCustomRangeType($1, $3); };
array_type_decl: ARRAY LB simple_type_decl RB OF type_decl      { $$ = makeArrayType($3, $6); };
record_type_decl: RECORD field_decl_list END                    { $$ = makeRecordType($2); };
field_decl_list: field_decl_list field_decl                     { $$ = linkFieldNodes($1, $2); }
               | field_decl                                     { $$ = makeFieldNode($1); };
field_decl: name_list COLON type_decl SEMI                      { $$ = makeFieldDecl($1, $3); };
name_list: name_list COMMA NAME         { $$ = linkNameNodes($1, $3); }
         | NAME                         { $$ = makeString($1); };

var_part: VAR var_decl_list             { $$ = $2; }
        |                               { $$ = makeEmptyNode(); };
var_decl_list: var_decl_list var_decl   { $$ = linkVarNodes($1, $2); }
             | var_decl                 { $$ = makeVarNode($1); };   
var_decl: name_list COLON type_decl SEMI                        { $$ = makeVarDecl($1, $3); };

routine_part: routine_part function_decl                        { $$ = linkFuncNodes($1, $2); }
            | routine_part procedure_decl                       { $$ = linkProcNodes($1, $2); }
            | function_decl                                     { $$ = makeFuncNode($1); }
            | procedure_decl                                    { $$ = makeProcNode($1); }
            |                                                   { $$ = makeEmptyNode(); };
function_decl: function_head SEMI sub_routine SEMI              { $$ = makeFuncDecl($1, $3); };
function_head: FUNCTION ID parameters COLON simple_type_decl    { $$ = makeFuncHead($2, $3, $5); };

procedure_decl: procedure_head SEMI sub_routine SEMI            { $$ = makeProcDecl($1, $3); };
procedure_head: PROCEDURE ID parameters                         { $$ = makeProcHead($2, $3); };

parameters: LP para_decl_list RP                                { $$ = $2; }
          |                                                     { $$ = makeEmptyNode(); };
para_decl_list: para_decl_list SEMI para_type_list              { $$ = linkParaNodes($1, $3); }
              | para_type_list                                  { $$ = makeParaNode($1); };
para_type_list: var_para_list COLON simple_type_decl            { $$ = makeParaDecl($1, $2); }
              |                                                 { $$ = makeEmptyNode(); };
var_para_list: VAR name_list                                    { $$ = makeRefVarList($2); };
val_para_list: name_list                                        { $$ = $1; };

routine_body: compound_stmt                     {};
compound_stmt: BEGIN stmt_list END              {};
stmt_list: stmt_list stmt SEMI |                {};
stmt: INTEGER COLON non_label_stmt              {};
    | non_label_stmt                            {};
non_label_stmt: assign_stmt                     {};
              | proc_stmt                       {};
              | compound_stmt                   {};
              | if_stmt                         {};
              | repeat_stmt                     {};
              | while_stmt                      {};
              | for_stmt                        {};
              | case_stmt                       {};
              | goto_stmt                       {};
assign_stmt: ID ASSIGN expression               {};
           | ID LB expression RB ASSIGN expression  {};
           | ID DOT ID ASSIGN expression        {};
proc_stmt: ID
         | ID LP args_list RP
         | SYS_PROC
         | SYS_PROC LP expression_list RP
         | READ LP factor RP                    {};
if_stmt: IF expression THEN stmt else_clause    {};
else_clause: ELSE stmt |                        {};
repeat_stmt: REPEAT stmt_list UNTIL expression  {};
while_stmt: WHILE expression DO stmt            {};
for_stmt: FOR ID ASSIGN expression direction expression DO stmt {};
direction: TO | DOWNTO                          {};
case_stmt: CASE expression OF case_expr_list END    {};
case_expr_list: case_expr_list case_expr | case_expr    {};
case_expr: const_value COLON stmt SEMI          {};
         | ID COLON stmt SEMI                   {};
goto_stmt: GOTO INTEGER                         {};
expression_list: expression_list COMMA expression | expression
expression: expression GE expr | expression GT expr
          | expression LE expr | expression LT expr
          | expression EQUAL expr | expression UNEQUAL expr | expr  {};
expr: expr PLUS term | expr MINUS term | expr OR term | term        {};
term: term MUL factor | term DIV factor | term MOD factor | term AND factor | factor    {};
factor: NAME | NAME LP args_list RP | SYS_FUNCT | SYS_FUNCT LP args_list RP |  const_value  |  LP  expression  RP
| NOT  factor | MINUS factor | ID LB expression RB | ID DOT ID {};
args_list: args_list COMMA expression | expression  {};
