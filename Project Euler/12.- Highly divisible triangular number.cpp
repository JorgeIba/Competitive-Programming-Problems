#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli div(lli n)
{
	lli contador=0;
	for (lli i=1; i*i<=n; i++)
	{
		if (n%i==0)
		{
			if (i*i == n)
			{
				contador++;
			}
			else
			{
				contador+=2;
			}
		}
	}
	
	return contador;
}



int main()
{
	lli i=0, cont=1;
	while(true)
	{
		i += cont;
		cont++;
		//cout<<i<<endl;
		if(div(i) > 500 )
		{
			cout<<i<<endl;
			break;		
		}
	}
	
	
	
	return 0;
}
