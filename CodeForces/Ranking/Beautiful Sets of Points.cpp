#include <bits/stdc++.h>
#define lli long long int
 
using namespace std;
 
int main()
{
	ios_base::sync_with_stdio(NULL);
	cout.tie(NULL);
	lli n,m;
	cin>>n>>m;
	lli res = min(n,m)+1;
	cout<<res<<endl;
	
	for(lli i=0; i<=(min(m,n)); i++)
	{
		cout<<i<<" "<<(m-i)<<endl;
	}
	
	
	return 0;
}
