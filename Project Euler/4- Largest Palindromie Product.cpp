#include <bits/stdc++.h>
using namespace std;

bool palindromo(int numero)
{
	int uno, dos, tres, cuatro, cinco, seis;
	if ((numero>=10000)and(numero<=99999))
	{
		cinco=numero%10;
		numero/=10;
		cuatro=numero%10;
		numero/=10;
		tres=numero%10;
		numero/=10;
		dos=numero%10;
		numero/=10;
		uno=numero%10;
		
		if ((cinco==uno)and(cuatro==dos))
		{
			return true;
		}
		else
		{
			return false;
		}
	
	}
	if ((numero>=100000)and(numero<=999999))
	{
		seis=numero%10;
		numero/=10;
		cinco=numero%10;
		numero/=10;
		cuatro=numero%10;
		numero/=10;
		tres=numero%10;
		numero/=10;
		dos=numero%10;
		numero/=10;
		uno=numero%10;
		
		if ((uno==seis)and(dos==cinco)and(tres==cuatro))
		{
			return true;
		}
		else
		{
			return false;
		}	
	}	
}

int main()
{
	int numero=0;
	for (int i=100; i<=999; i++)
	{
		for (int j=100; j<=999; j++)
		{
			if (palindromo(i*j))
			{
				if ((i*j)>numero)
				{
					numero=i*j;
				}
			}
		}
	}
	cout<<numero;
	return 0;
}
