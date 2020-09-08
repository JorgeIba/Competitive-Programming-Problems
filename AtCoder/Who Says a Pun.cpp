#include <bits/stdc++.h>
#define lli long long int
using namespace std;
lli sizee;
string cadena;

bool funcion(lli pos)
{
	lli contador=0;
	int j=pos+1;
	for (int i=1; i<=cadena.length()-pos; i++)
	{
		
		if (cadena[i] == cadena[j])
		{
			contador++;
			j++;
		}
		else
		{
			contador=0;
		}
		if (contador==pos)
		{
			return true;
		}
	}
	return false;
	
	
}



int main()
{
	cin>>sizee;
	cin>>cadena;
	cadena = 'a' + cadena;
	
	cout<<funcion(1)<<endl;
	cout<<funcion(2)<<endl;
	cout<<funcion(3)<<endl;
	cout<<funcion(4)<<endl;
	cout<<funcion(5)<<endl;
	cout<<funcion(6)<<endl;
	cout<<funcion(7)<<endl;
	cout<<funcion(8)<<endl;
	cout<<funcion(9)<<endl;
	
	return 0;
}
