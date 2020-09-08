#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
string simplif;
lli dp[1000010][3];


lli funcion(lli indice, lli estado)
{
	if(indice>=simplif.length())
	{
		return 0;
	}
	
	if(dp[indice][estado]!=-1)
	{
		return dp[indice][estado];
	}
	
	if((estado==0)and(simplif[indice]=='w'))
	{
		lli si= funcion(indice+1,1);
		lli no=funcion(indice+1,0);
		return dp[indice][estado]=si+no;
	}
	else if ((estado==0)and(simplif[indice]=='o'))
	{
		return funcion(indice+1,0);
	}
	else if((estado==1)and(simplif[indice]=='w'))
	{
		return funcion(indice+1,1);
	}
	else if((estado==1)and(simplif[indice]=='o'))
	{
		lli si=funcion(indice+1,2);
		lli no=funcion(indice+1,1);
		return dp[indice][estado]=si+no;
	}
	else if((estado==2)and(simplif[indice]=='w'))
	{
		lli si=1;
		lli no=funcion(indice+1,2);
		return dp[indice][estado]=si+no;
	}
	else if ((estado==2)and(simplif[indice]=='o'))
	{
		return funcion(indice+1,2);
	}
	
}




int main ()
{
	memset(dp, -1, sizeof(dp));
	string cadena;
	cin>>cadena;
	for (int i=1; i<cadena.length(); i++) 
	{
		if ((cadena[i]=='v')and(cadena[i-1]=='v'))
		{
			simplif+="w";
		}
		if (cadena[i]=='o')
		{
			simplif+="o";
		}
	}
	//cout<<simplif<<endl;
	cout<<funcion(0,0)<<endl;

	return 0;
}
