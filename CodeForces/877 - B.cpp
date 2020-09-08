#include <bits/stdc++.h>
#define lli long long int
using namespace std;

string cadena;


lli dp[5010][4];

lli funcion(lli indice, lli estado)
{
	if (indice>=cadena.length())
	{
		return 0;
	}
	if (dp[indice][estado]!=-1)
	{
		return dp[indice][estado];
	}
	if ((cadena[indice]=='b')and(estado==3))
	{
		return dp[indice][estado]=funcion(indice+1,3);
	}
	if((cadena[indice]=='b')and((estado==1)or(estado==2)))
	{
		lli si = funcion(indice + 1, 2) + 1;
		lli no = funcion(indice + 1,estado);
		return dp[indice][estado]= max(si,no);
	}
	if((cadena[indice]=='b')and(estado==0))
	{
		lli si = funcion(indice + 1, 2) + 1;
		lli no = funcion(indice + 1,0);
		return dp[indice][estado]= max(si,no);
	}
	if((cadena[indice]=='a')and((estado==0)or(estado==1)))
	{
		lli si=funcion(indice + 1, 1) + 1;
		lli no=funcion(indice+1,estado);
		return dp[indice][estado]= max(si,no);
	}
	if ((cadena[indice]=='a')and(((estado==2))or(estado==3)))
	{
		lli si=funcion(indice + 1, 3) + 1;
		lli no=funcion(indice+1, estado);
		return dp[indice][estado]= max(si,no);
	}
	
	
}

int main()
{
	memset(dp, -1, sizeof(dp));
	cin>>cadena;
	lli sumaA=0,sumaB=0;
	for(int i=0; i<cadena.length(); i++)
	{
		if(cadena[i]=='a')
		{
			sumaA++;
		}
		else
		{
			sumaB++;
		}
	}
	lli res=max(sumaA,sumaB);
	res=max(res, funcion(0,0));
	cout<<res<<endl;
	return 0;
}
