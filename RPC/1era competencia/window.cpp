#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	int frecuencia[26];
	memset(frecuencia, -1, sizeof(int)*26);
	string cadena;
	getline(cin, cadena);
	int tamano=cadena.length(), aux;
	for (int i=0; i<tamano; i++)
	{
		aux=cadena[i]-97;
		frecuencia[aux]++;
	}
	
	for (int i=0; i<26; i++)
	{
		cout<<frecuencia[i]<<" ";
	}
	
	return 0;
}
