#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n, pares=0, impares=0, aux;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		cin>>aux;
		if (aux%2==0)
		{
			pares++;
		}
		else
		{
			impares++;
		}
	}
	
	if (pares>=impares)
	{
		cout<<impares<<endl;
	}
	else
	{
		cout<<pares<<endl;
	}
	
	return 0;
}
