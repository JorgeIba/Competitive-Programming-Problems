#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	lli n;
	cin>>n;
	if (n%2==0)
	{
		cout<<(lli)(4)<<" "<<(lli)(n-4)<<endl;
	}
	else
	{
		cout<<(lli)(9)<<" "<<(lli)(n-9)<<endl;
	}
	
	return 0;
}
