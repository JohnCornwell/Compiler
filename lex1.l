%{
//#include "yaccExample.h"
#include "IOMngr.h"
#include "y.tab.h"

#define YY_INPUT(buf,result,max_size) \
	{ int c = getNextSourceChar(); \
          result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }
%}


letter [A-Za-z]
digit [0-9]

%%
if							{return IF;}
else						{return ELSE;}
while						{return WHILE;}
for							{return FOR;}
int							{return Int;}
void						{return Void;}
bool						{return Boolean;}
true						{return True;};
false						{return False;};
print						{return Write;}
printline					{return WriteLine;}
printspaces					{return WriteSpaces;}
read						{return Read;}
return						{return RETURN;}
{letter}({letter}|{digit})*	{return Ident;}
{digit}{digit}*				{return IntLit;}
\=\=						{return EQ;}
\<							{return LT;}
\<\=						{return LEQ;}
\>							{return GT;}
\>\=						{return GEQ;}
\!\=						{return NEQ;}
\&\&						{return AND;}
\|\|						{return OR;}
\=							{return '=';}
\+							{return '+';}
\-							{return '-';}
\*							{return '*';}
\/							{return '/';}
\%							{return '%';}
\^							{return '^';}
\!							{return '!';}
\;							{return ';';}
\,							{return ',';}
\{							{return '{';}
\}							{return '}';}
\(							{return '(';}
\)							{return ')';}
\[							{return '[';}
\]							{return ']';}
[ ]							{}
\t							{}
\r							{}
\n							{}

.				{writeIndicator(getCurrentColumnNum());
				   writeMessage("Illegal Character in lex");}

%%

	
int yywrap () {
    return 1;
}