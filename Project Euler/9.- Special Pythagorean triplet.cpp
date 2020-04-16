#include <bits/stdc++.h>
using namespace std;

struct smn
{
	int a;
	int b;
	int c;
};


int main()
{
	int a,b,c, suma;
	set<int> cuadrados;
	vector<smn> candidatos;
	smn* aux=new smn;
	for (int i=1; i<=1000; i++)
	{
		cuadrados.insert(i*i);
	}
	
	for (int i=1; i<10000; i++)
	{
		for (int j=i; j<10000; j++)
		{
			suma= i*i + j*j;
			aux->a=i;
			aux->b=j;
			aux->c=suma;
			if (cuadrados.find(suma)!=cuadrados.end())
			{
				if ((i+j+sqrt(suma))==1000)
				{
					cout<<i<<" "<<j<<" "<<sqrt(suma);
					return 0;
				}
				
				//candidatos.push_back(*aux);
			}
		}
	}
	
	//for (int i=0; i<candidatos.size(); i++)
	{
//		if ((candidatos[i].a + candidatos[i].b+  sqrt(candidatos[i].c))==1000)
		{
	//		cout<<candidatos[i].a<<" "<<candidatos[i].b<<" "<<sqrt(candidatos[i].c)<<endl;	
		}
		
	}
	
	return 0;
}
