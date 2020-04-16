#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli suma=0;


void funcion(string auxiliar)
{
	if(auxiliar[0]=='|')
	{
		suma+= (auxiliar.length()*42);
	}
	else
	{
		lli enteros=0;
		lli contadorBarras=0;
		string auxiliarNumeros;
		for(lli i=0; i<auxiliar.length(); i++)
		{
			if((auxiliar[i]==',')or(auxiliar[i]=='-'))
			{
				continue;
			}
			if(auxiliar[i]=='|')
			{
				contadorBarras= (auxiliar.length()) - i ;
				break;
			}
			else
			{
				auxiliarNumeros+= auxiliar[i];
			}
		}
		enteros = stoi(auxiliarNumeros);
		//cout<<enteros<<endl;
		suma+= enteros*contadorBarras;
	}
	//cout<<suma<<endl;
	return;
}

int main()
{
	string auxiliar;
	while(cin>>auxiliar)
	{
		funcion(auxiliar);
	}
	//cout<<suma<<endl;
	lli parteEntera = suma/10;
	if(suma%10==0)
	{
		cout<<suma<<",-"<<endl;
	}
	else
	{
		suma = parteEntera*10 + 10;
		cout<<suma<<",-"<<endl;
	}
	
	
	return 0;
}
