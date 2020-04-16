#include <bits/stdc++.h>
using namespace std;


void funcion()
{
	unordered_set<int> check;
	int m,n;
	unordered_set<int> res;
	cin>>m>>n;
	vector<int> cost(n+1);
	int aux;
	for (int i=1; i<=n; i++)
	{
		cin>>cost[i];
		aux=m-cost[i];
		if (check.find(cost[i])==check.end())
		{
			check.insert(aux);
		}
		else
		{
			res.insert(cost[i]);
			res.insert(aux);
		}
	}

	for (int i=1; i<=n; i++)
	{
		if (res.find(cost[i])!=check.end())
		{
			cout<<i<<" ";
		}
	}
	cout<<endl;
	

	
}



int main()
{
	int t;
	cin>>t;
	for (int i=0; i<t; i++)
	{
		funcion();
	}
	return 0;
}
