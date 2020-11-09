%{
	int yylex();
	int yyerror();
	int main();
	int lab1();
	int lab2();
	int lab3();
	int push();
	int codegen_assign();
	int codegen();
%}
%token ID NUM WHILE
%right '='
%left '+' '-'
%left '*' '/'
%%

S : WHILE{lab1();} '(' E ')'{lab2();} E ';'{lab3();}
;
E :V '='{push();} E{codegen_assign();}
| E '+'{push();} E{codegen();}
| E '-'{push();} E{codegen();}
| E '*'{push();} E{codegen();}
| E '/'{push();} E{codegen();}
| '(' E ')'
| V
| NUM{push();}
;
V : ID {push();}
;
%%

#include "lex.yy.c"
#include<ctype.h>
char st[100][10];
int top=0;
char i_[2]="0";
char temp[3]="t";

int lnum=1;
int start=1;
int main()
{
	printf("Enter the expression : ");
	//yylex(); 
	yyparse();
}

int push()
{
	strcpy(st[++top],yytext);
}

int codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
	top-=2;
	strcpy(st[top],temp);
	i_[0]++;
}


int codegen_assign()
{
	printf("%s = %s\n",st[top-2],st[top]);
	top-=2;
}

int lab1()
{
	printf("L%d: \n",lnum++);
}

int lab2()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = not %s\n",temp,st[top]);
	printf("if %s goto L%d\n",temp,lnum);
	i_[0]++;
}

int lab3()
{
	printf("goto L%d \n",start);
	printf("L%d: \n",lnum);
}