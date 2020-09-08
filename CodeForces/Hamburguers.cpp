#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	string cadena;
	lli B=0, S=0, C=0;
	cin>>cadena;
	for (int i=0; i<cadena.length(); i++)
	{
		if (cadena[i]=='B')
		{
			B++;
		}
		else if (cadena[i]=='S')
		{
			S++;
		}
		else
		{
			C++;
		}
	}
	lli costosB,costosS,costosC, dispB, dispS, dispC, money;
	cin>>dispB>>dispS>>dispC;
	cin>>costosB>>costosS>>costosC;
	cin>>money;
	lli costosB2= costosB*B;
	lli costosS2= costosS*S;
	lli costosC2= costosC*C;
	
	//cout<<B<<" "<<S<<" "<<C<<endl;
	//cout<<costosB2<<" "<<costosS2<<" "<<costosC2<<endl;
	
	
	lli l=0, r=100000000000000;
	lli residuoB, residuoS, residuoC, respuesta=0, residuoTotal;
	while (l<=r)
	{
		lli posible=l + (r-l)/2;
		residuoB = (posible*(costosB2)) - dispB*costosB;
		residuoS = (posible*(costosS2)) - dispS*costosS;
		residuoC = (posible*(costosC2)) - dispC*costosC;
		if(residuoB<0)
		{
			residuoB=0;
		}
		if(residuoS<0)
		{
			residuoS=0;
		}
		if(residuoC<0)
		{
			residuoC=0;
		}
		residuoTotal=residuoB + residuoS + residuoC;
		if (residuoTotal - money <=0)
		{
			respuesta=posible;
			l=posible+1;
		}
		else
		{
			r=posible-1;
		}
	}
	cout<<respuesta<<endl;
	return 0;
}
