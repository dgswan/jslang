all: jslang

jslang:
	bison Parser.y
	flex Lexer.l
	gcc -o ../bin/jslang Parser.c Lexer.c main.c expression.c
clean:
	rm Parser.c Parser.h Lexer.c Lexer.h ../bin/jslang
