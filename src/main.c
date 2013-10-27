/*
 *main.c file
 */
 
#include "expression.h"
#include "Parser.h"
#include "Lexer.h"
 
#include <stdio.h>

int yyparse(SExpression **expression, yyscan_t scanner);
 
SExpression *getAST(const char *expr)
{
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;
 
    if (yylex_init(&scanner)) {
        // couldn't initialize
        return NULL;
    }
 
    state = yy_scan_string(expr, scanner);
 
    if (yyparse(&expression, scanner)) {
        // error parsing
        return NULL;
    }
 
    yy_delete_buffer(state, scanner);
 
    yylex_destroy(scanner);
 
    return expression;
}
 
int evaluate(SExpression *e)
{
    switch (e->type) {
        case eVALUE:
            return e->value;
        case eMULTIPLY:
            return evaluate(e->left) * evaluate(e->right);
        case ePLUS:
            return evaluate(e->left) + evaluate(e->right);
        case eMINUS:
            return evaluate(e->left) - evaluate(e->right);
        case eDIVIDE:
            return evaluate(e->left) / evaluate(e->right);
        default:
            // shouldn't be here
            return 0;
    }
}

void printTree(SExpression *e, int depth) {
	int i;
	if (e == NULL)
		return;
	for (i = 0; i < depth; i++) {
		printf(" ");
	}
	depth++;
	switch (e->type) {
		case eVALUE:
			printf("%d\n", e->value);
			break;
		case eMULTIPLY:
			printf("*\n");
			break;
		case ePLUS:
			printf("+\n");
			break;
		case eMINUS:
			printf("-\n");
			break;
		case eDIVIDE:
			printf("/\n");
			break;
	}
	printTree(e->left, depth);
	printTree(e->right, depth);
	depth--;
}
 
int main(void)
{
    int depth = 0;
    SExpression *e = NULL;
    char test[]=" 4 + 2*10/5 + 3*( 5 + 1 ) - 4";
    int result = 0;
 
    e = getAST(test);
 
    result = evaluate(e);
    printTree(e, depth);
 
    printf("Result of '%s' is %d\n", test, result);
 
    deleteExpression(e);
 
    return 0;
}


