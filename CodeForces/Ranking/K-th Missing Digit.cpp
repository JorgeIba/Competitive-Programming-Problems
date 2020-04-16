#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli sizeA, sizeB, sizeC, aux;
	lli sumaA=0, sumaB=0, sumaC=0, res =0;
	string a, b, c;
	cin>>sizeA>>sizeB>>sizeC;	
	cin>>a>>b>>c;
	
	
	for (int i=0; i<sizeA; i++)
	{
		aux = a[i] - '0';
		sumaA= (sumaA + aux)%9;
	}
	
	

	for (int i=0; i<sizeB; i++)
	{
		aux = b[i] - '0';
		sumaB= (sumaB + aux)%9;
	}
	

	for (int i=0; i<sizeC; i++)
	{
		if(c[i] != '*')
		{
			aux = c[i] - '0';
			sumaC= (sumaC + aux)%9;	
		}
	}
	lli multiplicacion = (sumaA*sumaB)%9;
	

	if(sumaC < multiplicacion)
	{
		res = 	multiplicacion - sumaC;
	}
	else
	{
		res = (9 - sumaC) + multiplicacion;
	}
	
	cout<<res<<endl;
	
	
	return 0;
}
