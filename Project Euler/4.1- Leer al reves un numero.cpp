#include <bits/stdc++.h>
using namespace std;

int reves(int n)
{
	int reverso=0;
	while(n>0)
	{
		reverso=10*reverso + n%10;
		n=n/10;
	}
	cout<<reverso;
	return reverso;
}


int main()
{
	reves(12345);
	return 0;
}
