#include <stdlib.h>
#include <string.h>
#include "Token.h"


Token makeTokenForResv(reserved_word resv) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = RESERVED;
	tok->tokenval.resv = resv;
}

Token makeTokenForSys(sys_word sys) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = SYSTEM;
	tok->tokenval.sys = sys;
}

Token makeTokenForDeli(delimiter deli) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = DELI;
	tok->tokenval.deli = deli;
}

Token makeTokenForInt(int i) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = INTEGER;
	tok->tokenval.intval = i;
}

Token makeTokenForRear(double r) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = REAL;
	tok->tokenval.realval = r;
}

Token makeTokenForChar(char c) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = CHAR;
	tok->tokenval.charval = c;
}

Token makeTokenForString(char *s) {
	Token *tok = (Token *)malloc(sizeof(struct Token));
	tok->kind = STRING;
	strcpy(tok->tokenval.stringval, s);
}
