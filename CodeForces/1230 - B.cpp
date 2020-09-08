#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli s,k;
	string cadena;
	cin>>s>>k;
	cin>>cadena;
	for (int i=0; i<s; i++)
	{
		
		if ((i==0)and(cadena[i]==1)and(s!=1))
		{
			continue;
		}
		else if ((i==0)and(cadena[i]=='0')and(s==1))
		{
			continue;
		}
		else if ((i!=0)and(cadena[i]=='0')and(s!=1))
		{
			continue;
		}
		else if ((i==0)and(cadena[i]!='1')and(s!=1)and(k!=0))
		{
			cadena[i]='1';
			k--;
		}
		else if((i==0)and(s==1)and(k!=0))
		{
			cadena[i]='0';
			k--;
		}
		else if ((i!=0)and(k!=0))
		{
			cadena[i]='0';
			k--;
		}
		if (k==0)
		{
			break;
		}
	}
	cout<<cadena<<endl;
	return 0;
}
