#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli esPrimo(lli n)
{
	for(lli i=3; i*i<=n; i+=2)
	{
		if (n%i==0)
		{
			return i;
		}
	}
	return -1;
}


int main()
{
	lli n;
	cin>>n;
	if (n%2==0)
	{
		cout<<(lli)(n/2)<<endl;
	}
	else
	{
		lli aux= esPrimo(n);
		if(aux==-1)
		{
			cout<<1<<endl;
		}
		else
		{
			cout<<(lli)((n-aux)/2 + 1)<<endl;
		}
	}
	return 0;
}
