#include <bits/stdc++.h>
using namespace std;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	long long int n, k;
	cin>>n>>k;
	vector< pair<long long int,long long int> > coordenadas(n);
	for (int i=0; i<n; i++)
	{
		cin>>coordenadas[i].first>>coordenadas[i].second;
	}
	pair <long long int, long long int> q;
	for (int i=0; i<k; i++)
	{
		cin>>q.first>>q.second;
		for (int j=0; j<n; j++)
		{
			if ((q.first==coordenadas[j].first)and(q.second==coordenadas[j].second))
			{
				cout<<0<<endl;
				break;
			}
			else
			{
				cout<<1<<endl;
				break;
			}
		}
	}
	return 0;
}
