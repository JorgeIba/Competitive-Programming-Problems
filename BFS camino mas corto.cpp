#include <bits/stdc++.h>
using namespace std;

vector<int> edges[10001];
bool visited[100001];
int longitud[100001];

void inicializar()
{
	for (int i=0; i<100001; i++)
	{
		visited[i]=false;
	}
}



int funcion(int buscar)
{
	queue<int> cola;
	cola.push(1);
	longitud[1]=1;
	visited[1]=true;
	while(!cola.empty())
	{
		int aux=cola.front();
		cola.pop();
		for (int i=0; i<edges[aux].size(); i++)
		{
			if (visited[edges[aux][i]]!=true)
			{
				visited[edges[aux][i]]=true;
				cola.push(edges[aux][i]);
				longitud[edges[aux][i]]=longitud[aux]+1;
			}
		}
	}
}
int main()
{
	inicializar();
	int cantidadAristas=0, a=0, b=0, buscar=0;
	cin>>cantidadAristas;
	for (int i=0; i<cantidadAristas; i++)
	{
		cin>>a>>b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	cin>>buscar;
    funcion(buscar);
    cout<< longitud[buscar];
    return 0;
}
