#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli numero, contador=0, aux;
	cin>>numero;
	if (numero/100>=1)
	{
		aux=(int) numero/100;
		numero=numero-aux*100;
		contador+=aux;
	}
	if ((numero/100<1)and(numero/20>=1))
	{
		aux=(int) numero/20;
		numero=numero-aux*20;
		contador+=aux;
	}
	if ((numero/20<1)and(numero/10>=1))
	{
		aux=(int) numero/10;
		numero=numero-aux*10;
		contador+=aux;
	}
	if ((numero/10<1)and(numero/5>=1))
	{
		aux=(int) numero/5;
		numero=numero-aux*5;
		contador+=aux;
	}
	if ((numero/5<1)and(numero>=1))
	{
		aux=numero;
		numero=numero-aux;
		contador+=aux;
	}
	cout<<contador<<endl;
		
	return 0;
}
