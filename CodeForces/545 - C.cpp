#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n;
	cin>>n;
	vector< pair<int,int> >	arboles(n);
	for (int i=0; i<n; i++)
	{
		cin>>arboles[i].first>>arboles[i].second;
	}
	if (n==1)
	{
		cout<<1<<endl;
		return 0;
	}
	lli contador=2;
	
	for (int i=1; i<n-1; i++)
	{
		lli auxF=arboles[i].first, auxS=arboles[i].second;
		
		if (auxF - auxS > arboles[i-1].first)
		{
			contador++;
		}
		else if (auxF + auxS < arboles[i+1].first)
		{
			arboles[i].first=auxF+auxS;
			contador++;
		}
		else
		{
			continue;
		}
		
	}
	cout<<contador<<endl;
	
	return 0;
}
