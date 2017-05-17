%{
#include <iostream>
#include <stdio.h>  
#include <fstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <map>
  
#define INT_TYPE 0
#define FLOAT_TYPE 1
#define BOOLEAN_TYPE 2
  
  extern  FILE *yyin;

  using namespace std;

  extern int yylex();
  void yyerror(const char *s);
  string getNextLabel(int n);
  string getNextLabel();
  vector<int> * append(vector<int> *a, vector<int> *b);
  void updateGoto(vector<int> *v, int index);
  
  vector<string> code;
  map<string, pair<int, int>> symbolTable;
  string outputFile = "hamada.j";
  int variableNum = 1;
  int labelCount = 0;
  %}

%start METHOD_BODY

%token SIMI_COLON
%token OPEN_PRAN CLOSE_PRAN
%token COMMA TRUE FALSE
%token CLOSE_BRACE OPEN_BRACE
%token if_T else_T while_T boolean_T int_T float_T
%token MOD OR AND ASSIGN
%define parse.error verbose

%code requires {
  #include <vector>
  using namespace std;
 }

%union {
  int expressionType;
  int primitiveType;
  int intValue;
  float floatValue;
  char *opValue;
  char *identifierName;

  struct { vector<int> *gotoList; } statementType;
  struct { vector<int> *trueList, *falseList; } booleanExpressionType;
}

%type <expressionType> EXPRESSION
%type <primitiveType> PRIMITIVE_TYPE
%type <opValue>  INFIX_OPERATOR
%type <opValue> BOOLEAN_OPERATOR
%type <intValue> GOTO
%type <intValue> LABEL
%type <statementType> STATEMENT
%type <statementType> STATEMENT_LIST
%type <statementType> IF
%type <statementType> WHILE
%type <booleanExpressionType> BOOLEAN_EXPRESSION

%token <identifierName> IDENTIFIER
%token <intValue> INTEGER
%token <floatValue> REAL
%token <opValue> PLUSE MINUS MUL DIV
%token <opValue> GREATER_THAN LESS_THAN GREATER_THAN_EQUAL EQUAL NOT_EQUAL LESS_THAN_EQUAL
%%

METHOD_BODY : STATEMENT_LIST LABEL
{
  updateGoto($1.gotoList, $2); 
  ofstream out("hamada.j");
  /// print header
  out << ".source hamada.j" << endl;
  out << ".class public test\n.super java/lang/Object\n" << endl;
  out << ".method public <init>()V" << endl;
  out << "aload_0" << endl;
  out << "invokenonvirtual java/lang/Object/<init>()V" << endl;
  out << "return" << endl;
  out << ".end method\n" << endl;
  out << ".method public static main([Ljava/lang/String;)V" << endl;
  out << ".limit locals 100\n.limit stack 100" << endl;
  out << ".line 1" << endl;
  
  for (string x : code) {
    out << x << "\n";
  }

  /// print footer
  out << "return" << "\n";
  out << ".end method" << "\n";
}
;

STATEMENT_LIST :
STATEMENT
| STATEMENT LABEL STATEMENT_LIST
{
  updateGoto($1.gotoList, $2);
  $$.gotoList = $3.gotoList;
}
;

STATEMENT :
DECLARATION { vector<int> *v = new vector<int>(); $$.gotoList = v; }
| IF { $$.gotoList = $1.gotoList; }
| WHILE { $$.gotoList = $1.gotoList; }
| ASSIGNMENT { vector<int> *v = new vector<int>(); $$.gotoList = v; }
;

DECLARATION : PRIMITIVE_TYPE IDENTIFIER SIMI_COLON
{
  symbolTable[$2] = make_pair(variableNum++, $1);
  if ($1 == INT_TYPE) {
    code.push_back("iconst_0\nistore " + to_string(variableNum - 1));
  } else if ($1 == FLOAT_TYPE) {
    code.push_back("fconst_0\nfstore " + to_string(variableNum - 1));
  } else {
    /// ADD boolean
    printf("Error boolean not supported");
  }
}
;

PRIMITIVE_TYPE : int_T { $$ = INT_TYPE; }
| boolean_T { $$ = BOOLEAN_TYPE; }
| float_T { $$ = FLOAT_TYPE; }
;

GOTO : { $$ = code.size(); code.push_back("goto "); }

LABEL : { $$ = labelCount; code.push_back(getNextLabel() + ":"); }

IF :
if_T OPEN_PRAN
BOOLEAN_EXPRESSION CLOSE_PRAN
OPEN_BRACE
LABEL
STATEMENT_LIST GOTO CLOSE_BRACE
else_T OPEN_BRACE
LABEL
STATEMENT_LIST CLOSE_BRACE
{
  updateGoto($3.trueList, $6);
  updateGoto($3.falseList, $12);
  $$.gotoList = append($7.gotoList, $13.gotoList);
  $$.gotoList->push_back($8);
}
;

WHILE :
LABEL
while_T OPEN_PRAN BOOLEAN_EXPRESSION CLOSE_PRAN
OPEN_BRACE LABEL
STATEMENT_LIST CLOSE_BRACE
{
  code.push_back("goto " + getNextLabel($1));
  updateGoto($8.gotoList, $1);
  updateGoto($4.trueList, $7);
  $$.gotoList = $4.falseList;
}
;

ASSIGNMENT : IDENTIFIER ASSIGN EXPRESSION SIMI_COLON
{
  if ($3 == INT_TYPE) {
    code.push_back("istore " + to_string(symbolTable[$1].first));
  } else {
    code.push_back("fstore " + to_string(symbolTable[$1].first));
  }
}
;

EXPRESSION :
INTEGER { $$ = INT_TYPE; code.push_back("ldc " + to_string($1));}
| REAL { $$ = FLOAT_TYPE; code.push_back("ldc " + to_string($1));}
| EXPRESSION INFIX_OPERATOR EXPRESSION
{
  string str($2);
  if ($1 == FLOAT_TYPE && $3 == FLOAT_TYPE) {
    $$ = FLOAT_TYPE;
    code.push_back("f" + str);
  } else if ($1 == INT_TYPE && $3 == INT_TYPE) {
    $$ = INT_TYPE;
    code.push_back("i" + str);
  } else {
    printf("error can't add float to int\n");
  }
}
| IDENTIFIER
{
  $$ = symbolTable[$1].second;
  if ($$ == INT_TYPE) {
    code.push_back("iload " + to_string(symbolTable[$1].first));
  } else {
    code.push_back("fload " + to_string(symbolTable[$1].first));
  }
}
| OPEN_PRAN EXPRESSION CLOSE_PRAN { $$ = $2; }
;

INFIX_OPERATOR : PLUSE { $$ = $1; }
| MINUS { $$ = $1; }
| MUL { $$ = $1; }
| DIV { $$ = $1; }
;

BOOLEAN_OPERATOR: GREATER_THAN
| LESS_THAN
| GREATER_THAN_EQUAL
| EQUAL
| NOT_EQUAL
| LESS_THAN_EQUAL
;

BOOLEAN_EXPRESSION:
TRUE
{
  $$.trueList = new vector<int>();
  $$.falseList = new vector<int>();
  $$.trueList->push_back(code.size());
  code.push_back("goto ");
}
| FALSE
{
  $$.trueList = new vector<int>();
  $$.falseList = new vector<int>();
  $$.falseList->push_back(code.size());
  code.push_back("goto ");
}
| EXPRESSION BOOLEAN_OPERATOR EXPRESSION
{
  string str($2);
  $$.trueList = new vector<int>();
  $$.falseList = new vector<int>();
  $$.trueList->push_back(code.size());
  $$.falseList->push_back(code.size() + 1);
  code.push_back(str + " ");
  code.push_back("goto ");
}
;
%%

void updateGoto(vector<int> *v, int index) {
  if (v) {
    for (int i = 0; i < v->size(); ++i) {
      code[(*v)[i]] = code[(*v)[i]] + getNextLabel(index);
    }
  }
}

vector<int> * append(vector<int> *a, vector<int> *b) {
  if (a && b) {
    vector<int> *res = new vector<int>(*a);
    res->insert(res->end(), b->begin(), b->end());
    return res;
  }
  else if (a) return a;
  else if (b) return b;
  else return new vector<int>();
}

string getNextLabel() {
  return "L_" + to_string(labelCount++);
}

string getNextLabel(int n) {
  return "L_" + to_string(n);
}

int main(void) {
#if YYDEBUG == 1
  extern int yydebug;
  yydebug = 1;
#endif
    yyin = stdin;
    do { 
      yyparse();
    } while(!feof(yyin));
    return 0;
}

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
