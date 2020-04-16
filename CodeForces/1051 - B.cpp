#include <bits/stdc++.h>
#define lli long long unsigned int

using namespace std;

int main()
{
	lli l,r;
	cin>>l>>r;
	cout<<"YES\n";
	for(lli i=l; i<=r; i+=2)
	{
		cout<<(lli)(i)<<" "<<(lli)(i+1)<<endl;
	}
	
	return 0;
}
