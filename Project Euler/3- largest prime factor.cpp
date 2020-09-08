#include <bits/stdc++.h>
#define lli long long unsigned int 
using namespace std;

int main()
{
	lli numero, i=2, factor;
	cin>>numero;
	while (numero>1)
	{
		while ((numero%i)==0)
		{
			
			cout<<i<<" ";
			if ((numero/i)==1)
			{
				cout<<i;
			}
			numero=numero/i;
		}
		
			i++;
		
	}
	return 0;
}
