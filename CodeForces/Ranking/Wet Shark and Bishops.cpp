#include <bits/stdc++.h>
#define lli long long int

using namespace std;

map<lli,lli> frequencyPos;
map<lli,lli> frequencyNeg;

lli Gauss(lli n)
{
	return n*(n+1)/2;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n;
	cin>>n;
	vector< pair<lli,lli> > coord(n);
	for(int i=0; i<n; i++)
	{
		cin>>coord[i].first>>coord[i].second;
	}

	for(auto x: coord)
	{
		lli auxPos = x.first + x.second;
		lli auxNeg = x.first - x.second;
		frequencyPos[auxPos]++;
		frequencyNeg[auxNeg]++;
	}
	lli suma=0;
	for(auto aux: frequencyPos)
	{
		lli contador = aux.second;
		if(contador>0)
		{
			suma+= Gauss(contador-1);
		}
	}

	for(auto aux: frequencyNeg)
	{
		lli contador = aux.second;
		if(contador>0)
		{
			suma+= Gauss(contador-1);
		}
	}
	cout<<suma<<endl;
	return 0;
}