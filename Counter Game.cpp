#include <bits/stdc++.h>
using namespace std;

stack<long long unsigned int> binarios;
long long unsigned int contador1=1;

void ContarBinario(long long unsigned int n)
{
    long long unsigned int i=1;
    long long unsigned int x=1;
    while ((x<<i)<=n)
    {
        binarios.push(x<<i);
        i++;
    }
}

void ContarUltimoBit(long long unsigned int n)
{
    long long unsigned int i=1;
    contador1=1;
    while ((n>>i)!=1)
    {
        contador1++;
        i++;
    }
}

long long unsigned int Potencia2Cercano(long long unsigned int n)
{
	while (binarios.size()!=0)
	{
		if (n>binarios.top())
		{
			return binarios.top();
		}
		else
		{
			
			binarios.pop();
		}
	}
	return 0;
}

bool EsONo(long long unsigned int n)
{
    bool res=true;
    res=(n&&(n&(n-1)));
    return res;
}


bool FuncionBergas()
{
    bool ganador=false;
    long long unsigned int n=0;
    cin>>n;
    
    ContarBinario(n);
    while (n!=1)
    {    
        ganador= !ganador;
        
        if (EsONo(n)==false)
        {
        	ContarUltimoBit(n);
            if ((contador1%2)!=0)
            {
                return ganador; 
            }
            else
            {
                return !ganador; 
            }
        }    
        else
        {
            n=n-Potencia2Cercano(n);
            binarios.pop();
        }
    };
    return ganador;
}

int main()
{
    ios::sync_with_stdio(false);
    int t=0;
    cin>>t;
    for (int i=0; i<t; i++)
    {
        if (FuncionBergas()==true)
        {
            cout<<"Louise\n";
        }
        else 
        {
            cout<<"Richard\n";
        }
    }
    return 0;
}

