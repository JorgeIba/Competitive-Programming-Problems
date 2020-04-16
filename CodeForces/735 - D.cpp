#include<bits/stdc++.h>
#define lli long long int
using namespace std;

bool esPrimo(lli n)
{
	for(lli i=2; i*i<=n; i++)
	{
		if (n%i==0)
		{
			return false;
		}
	}
	return true;
}




int main()
{
	lli n;
	cin>>n;
	if(esPrimo(n))
	{
		cout<<1<<endl;
		return 0;
	}
	if(n%2==0)
	{
		cout<<2<<endl;
	}
	else
 	{
 		if (esPrimo(n-2))
 		{
 			cout<<2<<endl;
		}
		else
		{
			cout<<3<<endl;
		}
	}
	
	return 0;
}
