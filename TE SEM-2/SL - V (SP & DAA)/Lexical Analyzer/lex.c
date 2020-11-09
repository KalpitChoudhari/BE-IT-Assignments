#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct IDN
{
	char *name;
	int srno;
}IDN;

struct LTR
{
	char *name;
	int srno;
}LTR;

struct terminal
{
	char *name;
	int srno;
}TRN;

struct UST
{
	char *class, *sym;
	int srno;
}UST;

void init(struct terminal TRN[])
{
	FILE *fp;
	fp = fopen("terminal.txt","r");
	
	for(int i=0;i<25;i++)
	{
		TRN[i].name = (char *)malloc(sizeof(char));
		fscanf(fp, "%d\t%s", &TRN[i].srno, TRN[i].name);
	}
	
	fclose(fp); 
}

void alloc(struct IDN IDN[], struct LTR LTR[], struct UST UST[])
{
	for(int i=0;i<20;i++)
	{
		IDN[i].name = (char *)malloc(sizeof(char));
		LTR[i].name = (char *)malloc(sizeof(char));
	}
	for(int i=0;i<50;i++){
		UST[i].class = (char *)malloc(sizeof(char));
		UST[i].sym = (char *)malloc(sizeof(char));	
	}
}

void performOP(struct terminal TRN[], struct IDN IDN[], struct LTR LTR[], struct UST UST[])
{
	FILE *ip, *ip2;
	ip = fopen("input.c","r");
	ip2 = fopen("input.c","r");
	
	char *c = (char *)malloc(sizeof(char));
	char *string = (char *)malloc(sizeof(char));
	char *temp = (char *)malloc(sizeof(char));
	char *numString = (char *)malloc(sizeof(char));
	char *symbol = (char *)malloc(sizeof(char));
	
	int i = 0;
	
	*temp = '\0';
	*string = '\0';
	*numString = '\0';
	*symbol = '\0';
	
	*c = fgetc(ip);
	while(*c != EOF)
	{
		if(isdigit(*c))
		{
			*temp = '\0';
			*numString = '\0';
			while(isdigit(*c) && *string == '\0')
			{
				strcpy(temp, c);
				strcat(numString, temp);
				*c = fgetc(ip);
			}
			printf("DIG = %s\n", numString);
			*string = '\0';
			*numString = '\0';
			*symbol = '\0';
		}
		if(!isalpha(*c) && *string != '\0' && *c != 46 && !isdigit(*c))
		{
			printf("STR = %s\n",string);
			*string = '\0';
		}
		if(*c == 32 || *c == 10 || *c == 9)
		{
			*c = fgetc(ip);
			*string = '\0';
			*numString = '\0';
			*temp = '\0';
			continue;
		}
		else if(*c == 35 || *c == 40 || *c == 41 || *c == 42 || *c == 43 || *c == 60 || *c == 62 || *c == 123 || *c == 124 || *c == 44 || *c == 61 || *c 						== 59 || *c == 60 || *c == 44 || *c == 45)
		{
			if(*c == 43 || *c == 61 || *c == 45)
			{
				while(*c == 43 || *c == 61 || *c == 45)
				{
					strcpy(temp, c);
					*c = '\0';
					strcat(symbol, temp);
					*c = fgetc(ip);
				}
				printf("SYM = %s\n",symbol);
			}
			else
				printf("SYM = %s\n", c);
			*symbol = '\0';
			*c = '\0';
			*string = '\0';
			*numString = '\0';
			*temp = '\0';
		}
		else
		{
			strcpy(temp, c);
			strcat(string, temp);	
		}
		
		*c = fgetc(ip);
	}
}

int main()
{
	struct terminal TRN[50];
	struct IDN IDN[20];
	struct LTR LTR[20];
	struct UST UST[70];
	
	init(TRN);
	alloc(IDN, LTR, UST);
	
	performOP(TRN, IDN, LTR, UST);
	return 0;
}
