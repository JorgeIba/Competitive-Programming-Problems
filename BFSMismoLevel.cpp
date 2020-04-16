#include <bits/stdc++.h>
using namespace std;

vector<int> edges[10001];
bool visited[100001];
int longitud[100001];
int cantidad=0;

void inicializar()
{
	for (int i=0; i<100001; i++)
	{
		visited[i]=false;
	}
}



void funcion(int buscar)
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
				if (longitud[edges[aux][i]]==buscar)
				{
					cantidad++;
				}
			}
		}
	}
}
int main()
{
	inicializar();
	int n=0, a=0, b=0, buscar=0;
	cin>>n;
	for (int i=0; i<n-1; i++)
	{
		cin>>a>>b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	cin>>buscar;
    funcion(buscar);
    cout<< cantidad;
    return 0;
}
