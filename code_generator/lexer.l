%option noyywrap

%{
#include "grammer.tab.h"
#include <iostream>
#include <string.h>
using namespace std;
#ifdef PRINT
#define TOKEN(t) {\
printf("Token: " #t "\n");\
return (t);\
}
#else
#define TOKEN(t) return(t);
#endif
#define YY_DECL int yylex()
%}
digit                   [0-9]
letter                  [a-zA-Z]
integer                 ("-"|"+")?{digit}+
real                    ("-"|"+")?{digit}+.{digit}+("E"{digit}+)?
id                      {letter}({letter}|{digit})*
%%                 
[ \t\n]
<<EOF>>                 {return 0;}
";"                     TOKEN(SIMI_COLON)
"=="                    { yylval.opValue = strdup("if_icmpeq");
                          TOKEN(EQUAL)
                        }
"!="                    { yylval.opValue = strdup("if_icmpne");
                          TOKEN(NOT_EQUAL)
                        }
"<"                     { yylval.opValue = strdup("if_icmplt");
                          TOKEN(LESS_THAN)
                        }
"<="                    { yylval.opValue = strdup("if_icmple");
                          TOKEN(LESS_THAN_EQUAL)
                        }
">"                     { yylval.opValue = strdup("if_icmpgt");
                          TOKEN(GREATER_THAN)
                        }
">="                    { yylval.opValue = strdup("if_icmpge");
                          TOKEN(GREATER_THAN_EQUAL)
                        }
"("                     TOKEN(OPEN_PRAN)
"||"                    TOKEN(OR)
"%"                     TOKEN(MOD)
"="                     TOKEN(ASSIGN)
"&&"                    TOKEN(AND)
")"                     TOKEN(CLOSE_PRAN)
"{"                     TOKEN(OPEN_BRACE)
"}"                     TOKEN(CLOSE_BRACE)
","                     TOKEN(COMMA)
"+"                     { yylval.opValue = strdup("add");
                          TOKEN(PLUSE)
                        }
"-"                     { yylval.opValue = strdup("sub");
                          TOKEN(MINUS)
                        }
"*"                     { yylval.opValue = strdup("mul");
                          TOKEN(MUL)
                        }
"/"                     { yylval.opValue = strdup("div");
                          TOKEN(DIV)
                        }
if                      TOKEN(if_T)
else                    TOKEN(else_T)
while                   TOKEN(while_T)
boolean                 TOKEN(boolean_T)
int                     TOKEN(int_T)
float                   TOKEN(float_T)
true                    TOKEN(TRUE)
false                   TOKEN(FALSE)			  
{id}                    { yylval.identifierName = strdup(yytext);
                          TOKEN(IDENTIFIER)
                        }
{integer}               { yylval.intValue = atoi(yytext);
                          TOKEN(INTEGER)
                        }
{real}                  { yylval.floatValue = atof(yytext);
                          TOKEN(REAL)
                        }
%%
