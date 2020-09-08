#include <bits/stdc++.h>
using namespace std;

int contadorTotal=0;
int target=0;
int potenciaDe=0;
int suma=0;
int limite=0;
int valorlimite=0;

void funcionPotencias(int valor)
{
	int potencia=pow(valor, potenciaDe);
	suma+=potencia;
	if (suma==target)
	{
		contadorTotal++;
		suma-=potencia;
		return;
	}
	if ((valor==valorlimite)or(suma>target))
	{
		suma-=potencia;
		return;
	}
	
	else if (valor!=valorlimite)
	{
		int i=1;
		while ((valor+i)<=(valorlimite))
		{
			funcionPotencias(valor+i);
			i++;
		}
		if (valor!=1)
		{
			suma-=potencia;
			return;	
		}
		else
		{
			int x=1;
			suma-=potencia;
			while((valor+x)<=(valorlimite))
			{
				funcionPotencias(valor+x);
				x++;
			}
		}
	}

}


int main()
{
	int i=0, temp=0;
	cin>>target>>potenciaDe;
	while (temp<target)
	{ 
		i++;
		temp=pow(i,potenciaDe);
		if (temp<=target)
		{
			limite=temp;
		}
		else if (temp>target)
		
		{
			i--;	
		}
	}
	valorlimite=i;
	funcionPotencias(1);
	cout<<contadorTotal;
	return 0;
}
