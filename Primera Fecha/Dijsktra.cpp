#include <bits/stdc++.h>
using namespace std;


bool visitados[10010];


void visit()



int main()
{
	int ciudades, caminos, querys, nuevosCaminos, x, y;
	memset(visitados, false, 10010*sizeof(bool));
	cin>>ciudades>>caminos;
	vector< vector<int> > edges(ciudades+1);
	for (int i=0; i<caminos; i++)
	{
		cin>>x>>y;
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	
	visit(edge, x);
	
	return 0;
}
