/*
	BATCH	: K-11
	NAME	: Kalpit Choudhari	(33315)
	LAB	: SL - V		(TE - 11)
*/
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <cstring>
#include <queue>
using namespace std;

int store_pos = 0, ltr_cnt = 0;
//Struct which stores all the "MNEMONICS". (MNEMONIC TABLE) 
struct code
{
	string mnemo;
	int opcode;
	string type;
}cd;

//Struct which stores all the infromation about "LITERALS". (LITERAL TABLE)
struct LITAB
{
	int srno;
	string lname;
	int addr;
}lt;

//Struct which stores all the infromation about "SYMBOLS". (SYMBOL TABLE)
struct SYMTAB
{
	int srno, addr;
	string symName;
}sym;

//Init function, which will get data from file(s) and store them in structure. 
void init(struct code cd[], struct LITAB lt[], struct SYMTAB sym[])
{
	fstream file2;
	int rc = 0;
	
	//Get all the data related to mnemonic in "cd" structure
	file2.open("mnemonic.txt", ios::in);
   	while(!file2.eof())
   	{
		file2 >> cd[rc].mnemo >> cd[rc].opcode >> cd[rc].type;
		rc++;
   	}
   	file2.close();

	//Get all the data related to Literal in "lt" structure
   	file2.open("Literal.txt", ios::in);
   	rc = 0;
   	while(!file2.eof())
   	{
   		file2 >> lt[rc].srno >> lt[rc].lname >> lt[rc].addr;
   		rc++;
   		ltr_cnt++; 
   	}
   	file2.close();
   	
	//Get all the data related to Symbol in "sym" structure   	
   	file2.open("symbol.txt", ios::in);
   	rc = 0;
   	while(!file2.eof())
   	{
   		file2 >> sym[rc].srno >> sym[rc].symName >> sym[rc].addr;
   		rc++;
   	}
   	file2.close();
}

//Find if "TOKEN" is "Symbol" or not
bool searchSYM(char *s)
{
	if(s[0] == 'S' && s[1] == ',')
		return true;
	else
		return false;
}

//Find if "TOKEN" is "Assembler" directive or not
bool searchAD(char *s)
{
	if(s[0] == 'A' && s[1] == 'D' && s[2] == ',')
		return true;
	else
		return false;
}

//Find if "TOKEN" is "Imeprative Statement" or not
bool searchIS(char *s)
{
	if(s[0] == 'I' && s[1] == 'S' && s[2] == ',')
		return true;
	else
		return false;
}

//Find if "TOKEN" is "Register" or not
bool searchREG(char *s)
{
	if(s[0] == 'R' && s[1] == ',')
		return true;
	else
		return false;
}

//Find if "TOKEN" is "Literal" or not
bool searchLIT(char *s)
{
	if(s[0] == 'L' && s[1] == ',')
		return true;
	return false;
}

//Function to perfom operation i.e. Converting I/P to Machine Code
void performOP(struct code cd[], struct LITAB lt[], struct SYMTAB sym[])
{
	int i = 0, mnemonic = -1, lc = -1, isIS = 0, cnt = 0, lc_cnt = 0, c_cnt = 0;
	string str;
	fstream file, ltr_pool;
	bool  isSymbol = false, isSYM = false, isAD = false, isREG = false, isLIT = false, symVal = true, flg1 = true;;
	
	//Input file
	file.open("final.txt", ios::in);
	ltr_pool.open("pooltable.txt", ios::in);
	cout<<"LC\tMN\tREG\tMEM\n";
	
	while(getline(file, str))			//Get line from file and store it in string
	{
		int l = str.length();
		char c[l + 1];
		strcpy(c, str.c_str());
		char *token = strtok(c, " ( )");	//Split the input file and store it in "TOKEN"
		
		while(token)
		{
			isAD  = searchAD(token);		//Check for ASSEMBLER DIRECTIVE
			isIS  = searchIS(token);		//Check for IMPERATIVE STATEMENT
			isREG = searchREG(token);		//Check for REGISTER
			isSYM = searchSYM(token);		//Check for SYMBOL
			isLIT = searchLIT(token);		//Check for LITERAL
			
			//If first token is Symbol, then ignore
			if(lc_cnt == 1)
			{
				if(token[0] == 'S' && token[1] == ',')
				{
					token = strtok(0," ( )");
					lc_cnt = 0;
					cnt = 0;
					continue;
				}
			}
			
			//If token is AD, then print '-' 
			if(isAD)
			{
				int n = atoi(token+3);
				if(n == 5 || n == 2)
				{
					cout<<"-\t-\t-\t-\t";
					int temp;
					for(i=store_pos;i<ltr_cnt;i++)
					{
						if(flg1)
						{
							temp = lt[i].addr;
							cout<<"\n-\t-\t"<<lt[i].lname<<"\t"<<lt[i].addr;
							flg1 = false;
						}
						else
						{
							if((temp+1) == lt[i].addr)
							{
								cout<<"\n-\t-\t"<<lt[i].lname<<"\t"<<lt[i].addr;
								temp++;
							}
							else
							{
								store_pos = i-1;
							}
						}						
					}
					flg1 = true;
				}
				else
					cout<<"-\t-\t-\t-\t";
				cnt++;
				lc_cnt++;
			}
			
			//If token is IS, then print it's OPCODE
			else if(isIS)
			{
				if(token[4] >= '0' && token[4] <= '9')
					cout<<token[3]<<token[4]<<"\t";
				else
				{
					cout<<"0"<<token[3]<<"\t";
					if(token[3] == '0')
					{
						cout<<"-\t-\t";
						token = strtok(0," ( )");
						lc_cnt = 0;
						cnt = 0;
						continue;
					}
				}
				cnt++;
				lc_cnt++;
				symVal = true;
			}
			
			//If token is REG, then print it's OPCODE
			else if(isREG)
			{
				cout<<"0"<<token[2]<<"\t";
				cnt++;
				lc_cnt++;
			}
			
			//If token is LT, then print it's ADDRESS which is present in LITERAL table
			else if(isLIT)
			{
				const char *s = (token + 2);
				int d = atoi(s);
				cout<<lt[d].addr<<"\t";
			}
			
			//If symbol comes after IS or REG then, print it's ADDRESS from SYMBOL table
			if(cnt == 2 || cnt == 3 || cnt == 4)
			{
				if(isSYM)
				{
					const char *s = (token + 2);
					int d = atoi(s);
					cout<<sym[d].addr<<"\t";
				}
			}
			if(cnt == 1)
			{
				if(symVal && isSYM)
				{
					const char *s = (token + 2);
					int d = atoi(s);
					cout<<"-\t"<<sym[d].addr<<"\t";
					symVal = false;
				}
			}
			//Check if lc_cnt is 0 i.e. token is LC. If it is, then convert it to integer and print it
			if(lc_cnt == 0 && !isAD && !isIS && !isREG)
			{
				const char *s = token;
				int d = atoi(s);
				cout<<d<<"\t";
				lc_cnt = 1;
			}
			token = strtok(0," ( )");
		}
		cout<<endl;
		cnt = 0;
		lc_cnt = 0;
	}	
}

//Main function;
int main()
{
	struct code cd[25];
	struct LITAB lt[25];
	struct SYMTAB sym[25];
	init(cd, lt, sym);		//Initialize all the structures to get the tables
   	performOP(cd, lt, sym);		//function to convert i/p file to machine code
}
