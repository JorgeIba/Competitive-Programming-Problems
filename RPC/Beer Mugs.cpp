#include <bits/stdc++.h>
#define lli long long int

using namespace std;
lli contador[20];


bool Palindromo()
{
	lli pares=0, impares=0;
	for(lli i=0; i<20; i++)
	{
		if(contador[i] % 2 ==0)
		{
			pares++;
		}
		else
		{
			impares++;
		}
	}
	
	if(impares>=2)
	{
		return false;
	}
	else
	{
		return true;
	}
}



int main()
{
	memset(contador, 0, sizeof(contador));
	lli basura;
	cin>>basura;
	string cadena;
	cin>>cadena;
	
	for(lli i=0; i<basura; i++)
	{
		lli auxiliar=0;
		auxiliar=cadena[i] - 97;
		contador[auxiliar]++;
	}
	
	for(lli i=cadena.length() - 1; i>=0; i-- )
	{
		if(Palindromo())
		{
			cout<<(i+1)<<endl;
			return 0;
		}
		else
		{
			lli auxiliar=0;
			auxiliar=cadena[i]-97;
			contador[auxiliar]--;
		}
	}
	
	
	
	return 0;
}
