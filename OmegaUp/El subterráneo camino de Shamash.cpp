#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int potencias[6];

string convertir(lli numero)
{
	string res;
	int unidades=0, decenas=0;
	unidades=numero%10;
	decenas=numero/10;
	for (int i=0; i<decenas; i++)
	{
		res+="L";
	}
	for (int i=0; i<unidades; i++)
	{
		res+="I";
	}
	return res;
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	memset(potencias, 0, sizeof(int)*6);
	lli numero, expo;
	int mayor=0;
	string resp;
	cin>>numero;
	for (int i=5; i>=0; i--)
	{
		expo=pow(60, i);
		if (numero>=expo)
		{
			potencias[i]=numero/expo;
			numero=numero%expo;
		}
	}
	
	for (int i=0; i<6; i++)
	{
		if (potencias[i]!=0)
		{
			mayor=max(mayor, i);
		}
	}
	for (int i=mayor; i>=0; i--)
	{
		resp+=convertir(potencias[i])+".";
	}
	resp.resize(resp.length()-1);
	cout<<resp;
	return 0;
}
