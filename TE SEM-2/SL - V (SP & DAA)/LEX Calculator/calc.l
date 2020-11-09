%{
#include "y.tab.h"
extern int yylval;
%}
%%
[0-9]+ {yylval = atoi(yytext); return NUMBER; }
[ \t] ; /* ignore whitespace */
\n return 0; /* logical EOF */
. return yytext[0]; /* common catch all , return any character otherwise not handled as a
single charcter token to parser */
%%
