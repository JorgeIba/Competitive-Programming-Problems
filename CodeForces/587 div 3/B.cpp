#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	vector< pair<lli,lli> > latas(n);
	for (int i=0; i<n; i++)
	{
		cin>>latas[i].first;
		latas[i].second=i+1;
	}
	sort(latas.rbegin(), latas.rend());
	lli suma=0;
	vector<lli> respuesta(n);
	for (int i=0; i<n; i++)
	{
		//cout<<latas[i].first<<endl;
		suma += latas[i].first*(i) + 1;
		respuesta[i]=latas[i].second;
	}
	
	cout<<suma<<endl;
	for (int i=0; i<n; i++)
	{
		cout<<respuesta[i]<<" ";
	}
	
	return 0;
}
