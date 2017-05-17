all: java-like

grammer.tab.c grammer.tab.h:	grammer.y
	bison -d -v grammer.y

lex.yy.c: lexer.l grammer.tab.h
	flex lexer.l

java-like: lex.yy.c grammer.tab.c grammer.tab.h
	g++ -std=c++11 -o java-like grammer.tab.c  lex.yy.c -DYYDEBUG -DPRINT

clean:
	rm java-like grammer.tab.c lex.yy.c grammer.tab.h
