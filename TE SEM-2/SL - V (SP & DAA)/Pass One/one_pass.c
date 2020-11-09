#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int lc = -1;
int number = 0;
struct code
{
	char *mnemo;
	int opcode;
	char *type;
}cd;

struct LITAB
{
	int srno;
	char *lname;
	int addr;
}lt;

struct LTR
{
	int srno;
	char *lname;
}lit;

struct SYMTAB
{
	int srno, addr;
	char *symName;
}sym;

struct POOLTAB
{
	int num;
};

struct TII
{
	int addr;
	char *name;
}tii;

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

void init(struct code cd[])
{
	FILE *file2;
	file2 = fopen("mnemonic.txt", "r+");

   	for(int i=0;i<22;i++)
   	{
   		cd[i].mnemo = (char *) malloc(sizeof(char));
		cd[i].type = (char *) malloc(sizeof(char));
   		fscanf(file2,"%s\t%d\t%s ",cd[i].mnemo, &cd[i].opcode, cd[i].type);
   	}
   	fclose(file2);
}

int searchMN(char *s, struct code cd[])
{
	for(int i=0;i<22;i++)
	{
		if(strcmp(cd[i].mnemo,s) == 0)
			return i;
	}
	return -1;
}

bool searchSYM(char *s, struct SYMTAB sym[])
{
	for(int i=0;i<20;i++)
	{
		if(!strcmp(sym[i].symName,s))
			return true;
	}
	return false;
}

bool searchTII(char *s, struct TII tii[])
{
	for(int i=0; i<10 ;i++)
	{
		if(!strcmp(tii[i].name,s))
			return true;
	}
	return false;
}

int search_dup_sym(char *s, struct SYMTAB sym[])
{
	for(int i=0;i<10;i++)
	{	
		if(!strcmp(sym[i].symName, s))
			return sym[i].addr;
	}
	return -1;
}

char oper(const char *s)
{
	char *p = NULL;
	long converted = strtol(s, &p, 10);
	if(converted != 0)
		return 'C';
	if(s[0] == '=')
		return 'L';
	else
		return 'S';
}
void alloc(struct LITAB lt[], struct LTR lit[],struct SYMTAB sym[], struct TII tii[])
{
	for(int i=0;i<25;i++)
	{
		lt[i].lname = (char *)malloc(sizeof(char));
		lit[i].lname = (char *)malloc(sizeof(char));
		sym[i].symName = (char *)malloc(sizeof(char));
		tii[i].name = (char *)malloc(sizeof(char));
	}
}
void performOP(struct code cd[])
{
	struct LITAB lt[25];
	struct LTR lit[25];
	struct SYMTAB sym[25];
	struct TII tii[25];
	struct POOLTAB pt[10];
	int i = 0, flag = 0, locMN = -1, fl = 0, poolno = 0, poolflag = 0, litflag = 0, count = 0, tiiCNT = 0, symCNT = 0, searchLOC = 0, n = 0, dup_litflag = 0, pool_no = 1;
	char pool;
	bool dup_flag = false, ds_flag = false, origin_flag = false;
	FILE *file, *output, *literal, *fin, *symbol, *location_cnt, *pool_tbl;
	file = fopen("demo.txt", "r+");	
   	output = fopen("output.txt","w");
   	literal = fopen("Literal.txt","w");
   	symbol = fopen("symbol.txt", "w");
   	pool_tbl = fopen("pooltable.txt","w");
   	  
   	alloc(lt,lit,sym,tii);	
   	char *s1 = NULL;
   	size_t len = 0;
   	while(getline(&s1, &len, file) != -1)
   	{
   		char *token = strtok(s1," ");
   		while(token) 
	    	{
	    		++count;
	    		token = trim(token);
	    		locMN = searchMN(token, cd);
	    		if(fl)
	    		{
	    			lc = atoi(token);
	    			lc--;
	    			fl = 0;
	    		}
	    		if(locMN == 11)
	    			fl = 1;
	    			
	    		if(ds_flag)
	    			lc += atoi(token);
	    		if(origin_flag)
	    		{
	    			bool plusFlag = false;
	    			char *s2 = (char *)malloc(sizeof(char));
	    			char *num = (char *)malloc(sizeof(char));
	    			int j = 0;
	    			for(int i=0;token[i]!='\0';i++)
	    			{
	    				if(token[i] == '+')
	    				{
	    					i++;
	    					j = 0;
	    					while(token[i]!='\0')
	    					{
	    						num[j] = token[i];
	    						j++;
	    						i++;
	    					}
	    					num[j] = '\0';
	    					plusFlag = true;
	    					break;
	    				}
	    				else
	    					s2[i] = token[i];
	    			}
	    			if(plusFlag)
	    				n = atoi(num)-1;
	    			searchLOC = search_dup_sym(s2, sym);
	    			if(searchLOC != -1)
	    			{
	    				lc = searchLOC + n;
	    			}
	    			else{
	    				lc = atoi(token) - 1;
	    			}
	    			origin_flag = false;
	    		}
	    		
			if(locMN != -1)
			{
				if(!strcmp(token,cd[locMN].mnemo))
				{
					if(!strcmp(cd[locMN].type,"AD"))
					{
						if((!strcmp(cd[locMN].mnemo,"LTORG")) || (!strcmp(cd[locMN].mnemo,"END")))
						{
							while(litflag)
							{
								if(!pool_no)
								{
									pt[poolno].num = poolno;
									fprintf(pool_tbl,"#%d\n",pt[poolno].num);
								}
								lt[poolno].srno = poolno;
								strcpy(lt[poolno].lname,lit[number].lname);
								lt[poolno].addr = lc++;
								fprintf(literal,"%d\t%s\t%d\n",lt[poolno].srno, lt[poolno].lname, lt[poolno].addr);
								poolflag = 1;
								pool_no = 1;
								poolno++;
								number++;
								litflag--;
							}
							number = 0;
						}

						if(!strcmp(cd[locMN].mnemo,"ORIGIN"))
							origin_flag = true;
						fprintf(output, "     (%s,%d)", cd[locMN].type, cd[locMN].opcode);
					}
					else
					{
						if(!strcmp(cd[locMN].type , "R") || !strcmp(cd[locMN].type,"DL"))
						{
							if(dup_flag)
								dup_flag = false;
							if(!strcmp(cd[locMN].mnemo, "DS"))
								ds_flag = true;
							fprintf(output, "  (%s,%d) ", cd[locMN].type, cd[locMN].opcode);
						}	
						else{	
							if(dup_flag)
							{
								fprintf(output, "  (%s,%d)", cd[locMN].type, cd[locMN].opcode);
								dup_flag = false;
							}
							else
							{		
								fprintf(output, "%d  (%s,%d)", lc,cd[locMN].type, cd[locMN].opcode);
							}
						}
					}
				}
			}
			else
			{
				char s = oper(token);
				if(s == 'L')
				{
					strcpy(lit[litflag].lname,token);
					lit[litflag].srno = dup_litflag;
					fprintf(output,"(L,%d)",lit[litflag].srno);
					litflag++;
					dup_litflag = litflag;
					pool_no = 0;
				}
				else if(s == 'S')
				{
					if(count == 2 || count == 3)
					{
						bool tflag = false;
						tflag = searchTII(token, tii);
						if(!tflag)
						{
							strcpy(tii[tiiCNT].name, token);
							tii[tiiCNT].addr = lc;
							tiiCNT++;
						}
					}
					else
					{
						sym[symCNT].addr = lc;
						bool sflag = false;
						sflag = searchSYM(token, sym);
						if(!sflag)
						{
							sym[symCNT].srno = symCNT;
							sym[symCNT].addr = lc;
							strcpy(sym[symCNT].symName, token);
							symCNT++;
						}
						
					}
					if(count == 2 || count == 3 || count == 4)
					{
						fprintf(output,"%2s",token);
					}
					else{
						fprintf(output,"%d",lc);
						fprintf(symbol, "%d\t%s\t%d\n", symCNT, token, lc);
						dup_flag = true;
					}
				}
				else
				{
					fprintf(output, "  (C,%s)",token);
				}
				s = '\0';
			
			}
			
			token = strtok(0, " ,"); 
	    	}
	    	count = 0;
	    	fprintf(output,"\n");
	    	if(poolflag)
	    	{
	    		lc--;
	   		poolflag = 0;
	    	}
	    	if(ds_flag)
	    	{
	    		lc--;
	    		ds_flag = false;
	    	}
	    	lc++;

	}
	fclose(output);
	int indexSYM;
	output = fopen("output.txt","r");
	fin = fopen("final.txt","w");
	bool data;
	*s1 = '\0';
   	len = 0;
   	while(getline(&s1, &len, output) != -1)
   	{
		int search_dup = -1;	
   		char *token = strtok(s1," ");
   		
   		while(token)
   		{
   			token = trim(token);
   			int fla = 0; 
   			for(int i=0;i<20;i++)
			{	
				if(!strcmp(token, sym[i].symName))
				{
					fprintf(fin," (S,%d)  ",sym[i].srno);
					fla = 1;
				}
			}
			if(!fla)
				fprintf(fin," %s ",token);
			token = strtok(0, " ");	
   	
   		}
   		fprintf(fin,"\n");
	}
	fclose(fin);
	fclose(output);
	fclose(file);
	fclose(literal);
}

int main()
{
	struct code cd[23];
	init(cd);
   	performOP(cd);
	return 0;
}	
