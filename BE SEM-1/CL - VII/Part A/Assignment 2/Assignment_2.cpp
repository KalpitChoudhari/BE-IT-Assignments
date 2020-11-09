/*
Title	:	Chinese Remainder Theorem
Author	:	Kalpit Choudhari
Roll No	:	43315
*/

#include <iostream>
#include <vector>

#define long long long int
using namespace std;

//Find Multiplicative inverse
int inv(int a, int m) 
{ 
    a = a % m; 
    for (int x = 1; x < m; x++) 
       if ((a * x) % m == 1) 
          return x; 
} 

//Find the value of x
int findX(std::vector<int> num, std::vector<int> rem) {
	int product = 1;
	int result = 0;
	int size = num.size();

	for(int n : rem)
		product *= n;

	//Calculate value of M
	std::vector<int> M(size);
	for(int i = 0; i < size; i++)
		M[i] = product / rem[i];
	cout<<endl;

	//Applyinig Multiplicative inverse of m_i to calculate x_i
	for(int i = 0; i < size; i++) {
		int x = inv(M[i], rem[i]);
		result += num[i] * x * M[i];
		cout<<"x"<<i+1<<" = "<<x<<"\n";
	}

	cout<<"Final Value of x is : ";
	cout<< (result % product)<<endl;	//Final result
}


int main() {
	std::vector<int> num(3);
	std::vector<int> rem(3);
	
	//Take values from user
	int a, m;
	for(int i = 0; i < 3; i++) {
		cout<<"Enter values of (a" <<i+1<<" and m"<<i+1<<") :"<<endl;
		cin>>a>>m;
		num[i] = a;
		rem[i] = m;
	}

	cout<<"Give Values are : \n";
	for(int i = 0; i < 3; i++) {
		cout<<"X = "<<num[i]<<" ( MOD "<<rem[i]<<" )"<<endl; 
	}
	//Calculate result
	findX(num, rem);
	return 0;
}