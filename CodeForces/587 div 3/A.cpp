#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli size;
	cin>>size;
	string cadena;
	cin>>cadena;
	lli contador=0;
	for (int i=0; i<cadena.length()-1; i=i+2)
	{
		lli contadora=0, contadorb=0;
		for (int j=0; j<2; j++)
		{
			if (cadena[i+j]=='a')
			{
				contadora++;
			}
			else
			{
				contadorb++;
			}
		}
		if(contadora>contadorb)
		{
			contador++;
			cadena[i]='b';
		}
		else if(contadora<contadorb)
		{
			contador++;
			cadena[i]='a';
		}
	}
	cout<<contador<<endl;
	cout<<cadena<<endl;
	
	return 0;
}
