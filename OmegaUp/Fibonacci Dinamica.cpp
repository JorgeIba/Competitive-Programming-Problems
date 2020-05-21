#include <bits/stdc++.h>
using namespace std;


long long int fibonacci(long long int fibo[],int n)
{
	if (fibo[n]!=0)
		{
			return fibo[n];
		}
	if (n==0)
	{
		return 0;
	}
	else if (n==1)
	{
		return 1;
	}
	fibo[n]=(fibonacci(fibo, n-1)+fibonacci(fibo, n-2));
	return fibo[n];
	
}


int main()
{
	int n;
	cin>>n;
	long long int fibo[n+1];
	memset(fibo, 0, sizeof(long long int)*(n+1));
	cout<<fibonacci(fibo, n);
	return 0;
}
