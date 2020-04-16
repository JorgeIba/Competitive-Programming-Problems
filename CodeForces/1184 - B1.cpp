#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli naves,bases;
	cin>>naves>>bases;
	vector<lli> power(naves);
	vector< pair<lli,lli> > oro(bases);
	for (int i=0; i<naves; i++)
	{
		cin>>power[i];
	}
	for (int i=0; i<bases; i++)
	{
		cin>>oro[i].first>>oro[i].second;
	}
	sort(oro.begin(), oro.end());
	for (int i=1; i<bases; i++)
	{
		oro[i].second+=oro[i-1].second;
	}
	for (int i=0; i<naves; i++)
	{
		lli l=0, r=bases-1, resp=-1;
		while(l<=r)
		{
			lli posible = l + (r-l)/2;
			if(power[i] >= oro[posible].first)
			{
				//cout<<power[i]<<" "<<oro[posible].first<<endl;
				resp=posible;
				l=posible+1;
			}
			else
			{
				r=posible-1;
			}
		}
		
		
		if(resp==-1)
		{
			cout<<0<<" ";
		}
		else
		{
			cout<<oro[resp].second<<" ";	
		}
		
	}
	
	return 0;
}
