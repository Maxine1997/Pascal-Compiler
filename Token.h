#ifndef TOKEN_H
#define TOKEN_H

enum reserved_word {
	AND,
	ARRAY,
	BEGIN,
	CASE,
	CONST,
	DIV,
	DO,
	DOWNTO,
	ELSE,
	END,
	FILE,
	FOR,
	FUNCTION,
	GOTO,
	IF,
	IN,
	LABEL,
	MOD,
	NIL,
	NOT,
	OF,
	OR,
	PACKED,
	PROCEDURE,
	PROGRAM,
	RECORD,
	REPEAT,
	SET,
	THEN,
	TO,
	TYPE,
	UNTIL,
	VAR,
	WHILE,
	WITH
};

enum sys_word {
	_FALSE,
	MAXINT,
	_TRUE,
	BOOLEAN,
	CHAR,
	INTEGER,
	REAL,
	ABS,
	CHR,
	ODD,
	ORD,
	PRED,
	SQR,
	SQRT,
	SUCC,
	WRITE,
	WRITELN
};

enum delimiter {
	ASSIGN,
	COLON,
	COMMA,
	DOT,
	DOTDOT,
	EQUAL,
	GE,
	GT,
	LB,
	LE,
	LP,
	LT,
	MINUS,
	UNEQUAL,
	PLUS,
	RB,
	RP,
	SEMI,
	SLASH,
	STAR
};

enum token_type {
	RESERVED,
	SYSTEM,
	DELI,
	INTEGER,
	REAL,
	CHAR,
	STRING
};

struct Token {
	token_type kind;
	union {
		reserved_word resv;
		sys_word sys;
		delimiter deli;
		int intval;
		double realval;
		char charval;
		char stringval[16];
	} tokenval;
};

Token makeTokenForResv(reserved_word resv);
Token makeTokenForSys(sys_word sys);
Token makeTokenForDeli(delimiter deli);
Token makeTokenForInt(int i);
Token makeTokenForRear(double r);
Token makeTokenForChar(char c);
Token makeTokenForString(char *s);

#endif