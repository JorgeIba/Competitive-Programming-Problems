#include <bits/stdc++.h>
#define lli long long unsigned int
using namespace std;
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli cantidad, gcdAux=0, res=0, aux;
	cin>>cantidad;
	for(lli i=0; i<cantidad; i++)
	{
		cin>>aux;
		gcdAux=__gcd(gcdAux, aux);
	}
 
	for (lli i=1; i*i<=gcdAux; i++)
	{
		if( gcdAux%i==0)
		{
			if (i*i == gcdAux)
			{
				res++;
			}
			else
			{
				res+=2;
			}
		}
	}
	cout<<res<<endl;
	
	return 0;
}
