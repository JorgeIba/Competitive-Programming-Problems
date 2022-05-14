#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli a,b,c,q, res;
	cin>>q;
	for(int i=0; i<q; i++) //O(q)
	{
		cin>>a>>b>>c;
		res=floor((a+b+c)/2);
		cout<<res<<endl;
	}
	return 0;
}
