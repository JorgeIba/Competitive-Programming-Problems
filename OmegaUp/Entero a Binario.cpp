#include <bits/stdc++.h>
using namespace std;

void imprime(int n)
{
	if (n>=2)
	{
		imprime(n/2);
		cout<<n%2;
	}
	else
	{
		cout<<n;
	}
	
}



int main()
{
	int n;
	cin>>n;
	imprime(n);
	return 0;
}
