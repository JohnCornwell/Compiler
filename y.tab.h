/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Ident = 258,
    IntLit = 259,
    Int = 260,
    Void = 261,
    Boolean = 262,
    Write = 263,
    WriteLine = 264,
    WriteSpaces = 265,
    Read = 266,
    IF = 267,
    ELSE = 268,
    WHILE = 269,
    FOR = 270,
    EQ = 271,
    LT = 272,
    LEQ = 273,
    GT = 274,
    GEQ = 275,
    NEQ = 276,
    AND = 277,
    OR = 278,
    True = 279,
    False = 280,
    RETURN = 281
  };
#endif
/* Tokens.  */
#define Ident 258
#define IntLit 259
#define Int 260
#define Void 261
#define Boolean 262
#define Write 263
#define WriteLine 264
#define WriteSpaces 265
#define Read 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define FOR 270
#define EQ 271
#define LT 272
#define LEQ 273
#define GT 274
#define GEQ 275
#define NEQ 276
#define AND 277
#define OR 278
#define True 279
#define False 280
#define RETURN 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "ExprEval.y" /* yacc.c:1909  */

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

#line 119 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
