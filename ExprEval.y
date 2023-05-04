%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOMngr.h"
#include "SymTab.h"
#include "Semantics.h"
#include "CodeGen.h"

extern int yylex();	/* The next token function. */
extern char *yytext;   /* The matched token text.  */
extern int yyleng;      /* The token text length.   */
extern int yyparse();
extern int yyerror(char *);
void dumpTable();

extern SymTab *table;
%}

%union{
	int num;
	long val;
	char * string;
	struct ExprRes * ExprRes;
	struct InstrSeq * InstrSeq;
	struct BExprRes * BExprRes;
	struct BExprResList * BExprResList;
	struct IdentList * IdentList;
	struct varList * varList;
	struct ParamList * ParamList;
}

%type <string> Id
%type <ExprRes> Num
%type <ExprRes> Factor
%type <ExprRes> Term
%type <ExprRes> Expr
%type <InstrSeq> StmtSeq
%type <InstrSeq> Stmt
%type <BExprRes> IfStmt
%type <InstrSeq> SetStmt
%type <InstrSeq> ESetStmt
%type <BExprRes> RExpr
%type <BExprRes> AExpr
%type <BExprRes> OExpr
%type <BExprRes> BExpr
%type <BExprResList> BExprList
%type <BExprResList> BEList
%type <IdentList> ReadList
%type <IdentList> RList
%type <varList> ParamList
%type <varList> PList
%type <varList> LocalList
%type <varList> LList
%type <ParamList> ArgList
%type <ParamList> AList
%type <ParamList> ArgBExpr
%type <ParamList> ArgOExpr
%type <ParamList> ArgAExpr
%type <ParamList> ArgRExpr
%type <ParamList> ArgExpr
%type <ParamList> ArgTerm
%type <ParamList> ArgFactor
%type <ParamList> ArgNum

%token Ident 		
%token IntLit 	
%token Int
%token Void
%token Boolean
%token Write
%token WriteLine
%token WriteSpaces
%token Read
%token IF
%token ELSE
%token WHILE
%token FOR
%token EQ
%token LT
%token LEQ
%token GT
%token GEQ
%token NEQ
%token AND
%token OR
%token True
%token False
%token RETURN

%%
Prog			:	Declarations StmtSeq									{Finish($2);};
Declarations	:	Dec Declarations										{};
Declarations	:															{};
Dec 			:	Int Id ';' 												{enterName(table, $2); enterSize(0, 0);};

				|	Int Id {enterName(table, $2);} '[' IntLit {enterSize(atoi(yytext), 1);} ']' ';' {};
				
				|	Boolean Id ';'											{enterName(table, $2); enterSize(1, 0);};
				
				|	Boolean Id {enterName(table, $2);} '[' IntLit {enterSize(atoi(yytext), 2);} ']' ';' {};
				
				
				
				|	Void Id {enterName(table, $2); makeFunction(0);} '(' ParamList ')' '{' LocalList {makeTable($5, $8, $2);} StmtSeq '}'	{addBody($2, $10);};
				|	Int Id {enterName(table, $2); makeFunction(1);} '(' ParamList ')' '{' LocalList {makeTable($5, $8, $2);} StmtSeq '}'	{addBody($2, $10);};
				|	Boolean Id {enterName(table, $2); makeFunction(2);} '(' ParamList ')' '{' LocalList {makeTable($5, $8, $2);} StmtSeq '}'	{addBody($2, $10);};

Stmt			:	RETURN BExpr ';'										{if($2->Expr && !($2->Expr->isBoolean)){
																				$$ = doIntReturn($2->Expr);
																			 }else{
																				$$ = doBoolReturn($2);
																			 }
																			};
Stmt			:	RETURN ';'												{$$ = doVoidReturn();};






StmtSeq 		:	Stmt StmtSeq											{$$ = AppendSeq($1, $2);};
StmtSeq			:															{$$ = NULL;};


Stmt			:	Id '(' ArgList ')' ';'									{$$ = getVoidFunction($1, $3);};



Stmt			:	WriteLine ';'											{$$ = doPrintLine();};
Stmt			:	WriteSpaces '(' Expr ')' ';'							{$$ = doPrintSpaces($3);};
Stmt			:	Write '(' BExprList ')' ';'								{$$ = doPrint($3);};
Stmt			:	Read '(' ReadList ')' ';'								{$$ = doRead($3);};


BExprList		:	BEList													{$$ = $1;};
				|															{$$ = NULL;};
ReadList		:	RList													{$$ = $1;};
				|															{$$ = NULL;};
ParamList		:	PList													{$$ = $1;};
				|															{$$ = NULL;};
LocalList		:	LList													{$$ = $1;};
				|															{$$ = NULL;};
ArgList			:	AList													{$$ = $1;};
				|															{$$ = NULL;};
BEList			:	BExpr 													{$$ = AppendExpr($1, NULL);};
				|	BExpr ',' BEList										{$$ = AppendExpr($1, $3);};	
				
RList			:	Id														{$$ = AppendRead($1, NULL, NULL);};
				|	Id '[' Expr ']'											{$$ = AppendRead($1, $3, NULL);};
				|	Id ',' RList											{$$ = AppendRead($1, NULL, $3);};
				|	Id '[' Expr ']' ',' RList								{$$ = AppendRead($1, $3, $6);};
				
				
PList			:	Int Id													{$$ = AppendVar($2, 0, NULL, 0, 0);};
				|	Boolean Id												{$$ = AppendVar($2, 1, NULL, 0, 1);};
				|	Int Id '[' ']'											{$$ = AppendVar($2, -1, NULL, 0, 0);};
				|	Boolean Id '[' ']'										{$$ = AppendVar($2, -2, NULL, 0, 1);};
				|	Int Id ',' PList										{$$ = AppendVar($2, 0, $4, 0, 0);};
				|	Boolean Id ',' PList									{$$ = AppendVar($2, 1, $4, 0, 1);};
				|	Int Id '[' ']' ',' PList								{$$ = AppendVar($2, -1, $6, 0, 0);};
				|	Boolean Id '[' ']' ',' PList							{$$ = AppendVar($2, -2, $6, 0, 1);};
				
LList			:	Int Id ';' LocalList												{$$ = AppendVar($2, 0, $4, 0, 0);};
				|	Boolean Id ';' LocalList											{$$ = AppendVar($2, 1, $4, 0, 1);};
				|	Int Id '[' IntLit {$<num>$ = atoi(yytext);} ']' ';' LocalList		{$$ = AppendVar($2, $<num>5, $8, 1, 0);};
				|	Boolean Id '[' IntLit {$<num>$ = atoi(yytext);} ']' ';' LocalList	{$$ = AppendVar($2, $<num>5, $8, 1, 1);};
				
				
				
				
				
				
				
				
				
AList			: ArgBExpr													{$$ = $1;};
				| ArgBExpr ',' AList										{$$ = $1; $$->Next = $3;};
				



ArgBExpr		:	ArgOExpr												{$$ = $1;};
ArgOExpr		:	ArgOExpr OR ArgAExpr									{$$ = $1;
																			 if($$->value){
																				$$->boolean = doImmBExpr($$->value, 1);
																			 }
																			 if($3->value){
																				$3->boolean = doImmBExpr($3->value, 1);
																			 }
																			 $$->boolean = doOr($$->boolean, $3->boolean);
																			 $$->value = NULL;
																			 $$->type = 1;
																			};
ArgOExpr		:	ArgAExpr												{$$ = $1;};
ArgAExpr		:	ArgAExpr AND ArgRExpr									{$$ = $1;
																			 if($$->value){
																				$$->boolean = doImmBExpr($$->value, 1);
																			 }
																			 if($3->value){
																				$3->boolean = doImmBExpr($3->value, 1);
																			 }
																			 $$->boolean = doAnd($$->boolean, $3->boolean);
																			 $$->value = NULL;
																			 $$->type = 1;
																			};
ArgAExpr		:	ArgRExpr												{$$ = $1;};
ArgRExpr		:	'!' ArgRExpr											{$$ = $2;
																			 if($$->value){
																				$$->boolean = doNot(doImmBExpr($$->value, 1));
																			 }else{
																				$$->boolean = doNot($$->boolean);
																			 }
																			 $$->value = NULL;
																			 $$->type = 1;
																			};
ArgRExpr		:	ArgExpr EQ ArgExpr										{$$ = $1;
																			 if($1->value && $3->value){
																				$$->boolean = doBExpr($1->value, $3->value, "eq");
																				$$->value = NULL;
																				$$->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free($3);
																			};
ArgRExpr		: 	ArgExpr LT ArgExpr										{$$ = $1;
																			 if($1->value && $3->value){
																				$$->boolean = doBExpr($1->value, $3->value, "lt");
																				$$->value = NULL;
																				$$->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free($3);
																			};
ArgRExpr		:	ArgExpr LEQ ArgExpr										{$$ = $1;
																			 if($1->value && $3->value){
																				$$->boolean = doBExpr($1->value, $3->value, "leq");
																				$$->value = NULL;
																				$$->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free($3);
																			};
ArgRExpr		:	ArgExpr GT ArgExpr										{$$ = $1;
																			 if($1->value && $3->value){
																				$$->boolean = doBExpr($1->value, $3->value, "gt");
																				$$->value = NULL;
																				$$->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free($3);
																			};
ArgRExpr		:	ArgExpr GEQ ArgExpr										{$$ = $1;
																			 if($1->value && $3->value){
																				$$->boolean = doBExpr($1->value, $3->value, "geq");
																				$$->value = NULL;
																				$$->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free($3);
																			};
ArgRExpr		:	ArgExpr NEQ ArgExpr										{$$ = $1;
																			 if($1->value && $3->value){
																				$$->boolean = doBExpr($1->value, $3->value, "neq");
																				$$->value = NULL;
																				$$->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free($3);
																			};
ArgRExpr		:	ArgExpr													{$$ = $1;};
ArgRExpr		:	True													{$$ = newPList(NULL, doImmBExpr(doIntLit("1"), 1), 1);};
ArgRExpr		:	False													{$$ = newPList(NULL, doImmBExpr(doIntLit("0"), 1), 1);};


ArgExpr			:	ArgExpr '-' ArgTerm										{$$ = $1;
																			 if($$->value){
																				$$->value = doOp($1->value, $3->value, "sub");
																			 }
																			 if($1->type !=0 || $3->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Subtraction with a non-integer.");
																				$$->type = 0;
																			 }
																			 free($3);
																			};
ArgExpr			:	ArgExpr '+' ArgTerm										{$$ = $1;
																			 if($$->value){
																				$$->value = doOp($1->value, $3->value, "add");
																			 }
																			 if($1->type !=0 || $3->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Addition with a non-integer.");
																				$$->type = 0;
																			 }
																			 free($3);
																			};
ArgExpr			:	ArgTerm													{$$ = $1;};
ArgTerm			:	ArgTerm '*' ArgFactor									{$$ = $1;
																			 if($$->value){
																				$$->value = doOp($1->value, $3->value, "mul");
																			 }
																			 if($1->type !=0 || $3->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Multiplication with a non-integer.");
																				$$->type = 0;
																			 }
																			 free($3);
																			};
ArgTerm			:	ArgTerm '/' ArgFactor									{$$ = $1;
																			 if($$->value){
																				$$->value = doDivOrMod($1->value, $3->value, "division");
																			 }
																			 if($1->type !=0 || $3->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Division with a non-integer.");
																				$$->type = 0;
																			 }
																			 free($3);
																			};
ArgTerm			:	ArgTerm '%' ArgFactor									{$$ = $1;
																			 if($$->value){
																				$$->value = doDivOrMod($1->value, $3->value, "mod");
																			 }
																			 if($1->type !=0 || $3->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Modulus with a non-integer.");
																				$$->type = 0;
																			 }
																			 free($3);
																			};
ArgTerm			:	ArgFactor												{$$ = $1;};
ArgFactor		:	ArgNum '^' ArgFactor									{$$ = $1;
																			 if($$->value){
																				$$->value = doPow($1->value, $3->value);
																			 }
																			 if($1->type !=0 || $3->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Exponentiation with a non-integer.");
																				$$->type = 0;
																			 }
																			 free($3);
																			};
ArgFactor		:	ArgNum													{$$ = $1;};
ArgNum 		 	: 	'(' ArgBExpr ')'    									{$$ = $2;};
ArgNum		  	: 	'-' ArgNum			   									{$$ = $2;
																			 if($$->value){
																				$$->value = doNeg($2->value);
																			 }
																			 if($$->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Negation on a non-integer.");
																				$$->type = 0;
																			 }
																			};
ArgNum			:	Id '(' ArgList ')'										{$$ = newPList(getIntFunction($1, $3), NULL, 0);
																			 if(!findName(table, $1) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
																			 }else if(((struct Attribute *) getCurrentAttr(table))->functType < 2){
																				$$->type = 0;
																			 }else{
																				$$->type = 1;
																			 }
																			};
ArgNum			:	IntLit													{$$ = newPList(doIntLit(yytext), NULL, 0);};
ArgNum			:	Id '[' Expr ']'											{$$ = newPList(doRval($1, $3, getType($1)), NULL, 0);
																			 if(getType($1) == -1){
																				$$->type = 0;
																			 }else if(getType($1) == -2){
																				$$->type = 1;
																			 }
																			};
ArgNum			:	Id														{$$ = newPList(getArg($1), NULL, getType($1));};
Stmt			:	IfStmt													{$$ = finishIf($1);};
IfStmt			:	IF '(' BExpr ')' '{' StmtSeq '}' 						{$$ = doIf($3, $6);};
IfStmt			:	IfStmt ELSE IF '(' BExpr ')' '{' StmtSeq '}' 			{$$ = doElseIf($1, $5, $8);};
Stmt			:	IfStmt ELSE '{' StmtSeq '}' 							{$$ = doElse($1, $4);};
Stmt			:	WHILE '(' BExpr ')' '{' StmtSeq '}'						{$$ = doWhile($3, $6);};
Stmt			:	FOR '(' SetStmt BExpr ';' ESetStmt ')' '{' StmtSeq '}'	{$$ = doFor($3, $4, $6, $9);};
Stmt			:	SetStmt													{$$ = $1;};
SetStmt			:	Id '=' BExpr ';'										{if($3->Expr){
																				$$ = doAssign($1, $3->Expr, NULL, 0);
																			 }else{
																				$$ = doAssign($1, getBooleanVal($3), NULL, 1);
																			 }
																			};
SetStmt			:	Id '[' Expr ']' '=' BExpr ';'							{if($6->Expr){
																				$$ = doAssign($1, $6->Expr, $3, -1);
																			 }else{
																				$$ = doAssign($1, getBooleanVal($6), $3, -2);
																			 }
																			};

ESetStmt		:	Id '=' BExpr											{if($3->Expr){
																				$$ = doAssign($1, $3->Expr, NULL, 0);
																			 }else{
																				$$ = doAssign($1, getBooleanVal($3), NULL, 1);
																			 }
																			};
ESetStmt		:	Id '[' Expr ']' '=' BExpr								{if($6->Expr){
																				$$ = doAssign($1, $6->Expr, $3, -1);
																			 }else{
																				$$ = doAssign($1, getBooleanVal($6), $3, -2);
																			 }
																			};
BExpr			:	OExpr													{$$ = $1;};
OExpr			:	OExpr OR AExpr											{$$ = doOr($1, $3);};
OExpr			:	AExpr													{$$ = $1;};
AExpr			:	AExpr AND RExpr											{$$ = doAnd($1, $3);};
AExpr			:	RExpr													{$$ = $1;};
RExpr			:	'!' RExpr												{$$ = doNot($2);};
RExpr			:	Expr EQ Expr											{$$ = doBExpr($1, $3, "eq");};
RExpr			: 	Expr LT Expr											{$$ = doBExpr($1, $3, "lt");};
RExpr			:	Expr LEQ Expr											{$$ = doBExpr($1, $3, "leq");};
RExpr			:	Expr GT Expr											{$$ = doBExpr($1, $3, "gt");};
RExpr			:	Expr GEQ Expr											{$$ = doBExpr($1, $3, "geq");};
RExpr			:	Expr NEQ Expr											{$$ = doBExpr($1, $3, "neq");};
RExpr			:	Expr													{$$ = doImmBExpr($1, 0);};
RExpr			:	True													{$$ = doImmBExpr(doIntLit("1"), 1);};
RExpr			:	False													{$$ = doImmBExpr(doIntLit("0"), 1);};	
Expr			:	Expr '-' Term											{$$ = doOp($1, $3, "sub");};
Expr			:	Expr '+' Term											{$$ = doOp($1, $3, "add");};
Expr			:	Term													{$$ = $1;};
Term			:	Term '*' Factor											{$$ = doOp($1, $3, "mul");};
Term			:	Term '/' Factor											{$$ = doDivOrMod($1, $3, "divide");};
Term			:	Term '%' Factor											{$$ = doDivOrMod($1, $3, "mod");};
Term			:	Factor													{$$ = $1;};
Factor			:	Num '^' Factor											{$$ = doPow($1, $3);};
Factor			:	Num														{$$ = $1;};
Num 		 	: 	'(' BExpr ')'    										{if($2->Expr){
																				$$ = $2->Expr;
																			 }else{
																				$$ = getBooleanVal($2);
																			 }
																			};
Num		  		: 	'-' Num			   										{$$ = doNeg($2);};
Num				:	IntLit													{$$ = doIntLit(yytext);};
Num				:	Id '(' ArgList ')'										{$$ = getIntFunction($1, $3);
																			 if(!findName(table, $1) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
																			 }else if(((struct Attribute *) getCurrentAttr(table))->functType < 2){
																				$$->isBoolean = 0;
																			 }else{
																				$$->isBoolean = 1;
																			 }
																			};
Num				:	Id														{if(getType($1) != 1){
																				$$ = doRval($1, NULL, 0);
																				$$->isBoolean = 0;
																			 }else{
																				$$ = doRval($1, NULL, 1);
																				$$->isBoolean = 1;
																			 }
																			};
Num				:	Id '[' Expr ']'											{if(getType($1) != -2){
																				$$ = doRval($1, $3, -1);
																				$$->isBoolean = 0;
																			 }else{
																				$$ = doRval($1, $3, -2);
																				$$->isBoolean = 1;
																			 }
																			};
Id				: 	Ident													{$$ = strdup(yytext);}
%%

int yyerror(char *s){
	writeIndicator(getCurrentColumnNum());
	writeMessage("Illegal Character in YACC.");
	return 1;
}