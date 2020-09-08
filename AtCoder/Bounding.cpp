#include <bits/stdc++.h>
#define prob(a,b) cout<<contador<<" "<<target<<endl;
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	long long int n, target, contador=0, res=0;
	cin>>n>>target;
	
	vector<int> reb(n);
	
	for (int i=0; i<n; i++)
	{
			cin>>reb[i];
	}
	
	for (int i=0; i<=n; i++)
	{
		if (contador<=target)
		{
			res++;
		}
			contador+=reb[i];
		
	}
	cout<<res<<endl;
	return 0;
}
