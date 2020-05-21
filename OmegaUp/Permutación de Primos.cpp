#include <bits/stdc++.h>
#define prueba cout<<"aqui?\n"
using namespace std;

bool igualesono(int numero, int comparar)
{
	stringstream num1;
	stringstream comp1;
	int aux1;
	int aux2;
	num1<<numero;
	comp1<<comparar;
	string num=num1.str();
	string comp=comp1.str();
	int cubeta1[10];
	int cubeta2[10];
	memset(cubeta1, 0, sizeof(int)*10);
	memset(cubeta2, 0, sizeof(int)*10);
	
	for (int i=0; i<4; i++)
	{
		aux1=num[i]-'0';
		aux2=comp[i]-'0';
		cubeta1[aux1]+=1;
		cubeta2[aux2]+=1;
	}
	for (int i=0; i<10; i++)
	{
		if (cubeta1[i]!=cubeta2[i])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	bool primos[9999];
	bool flag1=false;
	bool flag2=false;
	vector<int> prim;
	for (int i=2; i<9999; i++)
	{
		for (int j=2; j<9999; j++)
		{
			if (i*j<9999)
			{
				primos[i*j]=true;
			}
		}
	}
	for (int i=1000; i<9999; i++)
	{
		if (primos[i]==false)
		{
			prim.push_back(i);
		}
	}
	igualesono(1481,8411);
	int n=0;
	
	vector< pair<int,int> > restas;
	
	for(int i=0; i<prim.size(); i++)
	{
		n=prim[i];
		for (int j=i+1; j<prim.size(); j++)
		{
			flag1=igualesono(n, prim[j]);
			if (flag1)
			{
				for (int x=j+1; x<prim.size(); x++)
				{
					flag2=igualesono(prim[j], prim[x]);
					if (flag2)
					{
						if ((prim[j]-prim[i])==(prim[x]-prim[j]))
						{
							cout<<prim[i]<<" "<<prim[j]<<" "<<prim[x]<<endl;
						}					
					}
				}
			}
			
		}
	}
	
	
	
	
	
	return 0;
}
