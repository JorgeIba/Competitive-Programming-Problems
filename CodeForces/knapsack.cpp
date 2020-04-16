#include <bits/stdc++.h>
#define lli long long int
using namespace std;


int main()
{
	lli n,w;
	cin>>n>>w;
	vector< pair<lli,lli> > items(n);
	lli dp[w+1];
	
	for (int i=0; i<n; i++)
	{
		cin>>items[i].first>>items[i].second;
	}
	
	memset(dp, -1, sizeof(lli)*(w+1));
	dp[0]=0;
	for (int i=0; i<n; i++)
	{
		for (int j=1; j<=w; j++)
		{
			if (dp[j]!=-1)
			{
				dp[j*items[i].]
			}
		}
	}
	
	for (auto x: dp)
	{
		cout<<x<<" ";
	}
	
	return 0;
}
