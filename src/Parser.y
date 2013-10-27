%{

/*
 *Parser.y file
 * To generate the parser run: "bison Parser.y"
 */
 
#include "expression.h"
#include "Parser.h"
#include "Lexer.h"
 
//int yyerror(SExpression **expression, yyscan_t scanner, const char *msg) {
    // Add error handling routine as needed
//}
 
%}
 
%code requires {
 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
 
}
 
%output  "Parser.c"
%defines "Parser.h"
 
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }
 
%union {
    int value;
    SExpression *expression;
}
 
%left '+' TOKEN_PLUS '-' TOKEN_MINUS
%left '*' TOKEN_MULTIPLY '/' TOKEN_DIVIDE
 
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_DIVIDE
%token TOKEN_MULTIPLY
%token <value> TOKEN_NUMBER
 
%type <expression> expr
 
%%
 
input
    : expr { *expression = $1; }
    ;
 
expr
    : expr TOKEN_PLUS expr { $$ = createOperation( ePLUS, $1, $3 ); }
    | expr TOKEN_MULTIPLY expr { $$ = createOperation( eMULTIPLY, $1, $3 ); }
    | expr TOKEN_DIVIDE expr { $$ = createOperation( eDIVIDE, $1, $3 ); }
    | expr TOKEN_MINUS expr { $$ = createOperation( eMINUS, $1, $3 ); }
    | TOKEN_LPAREN expr TOKEN_RPAREN { $$ = $2; }
    | TOKEN_NUMBER { $$ = createNumber($1); }
    ;
 
%%



