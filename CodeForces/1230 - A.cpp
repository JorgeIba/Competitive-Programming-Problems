#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	vector<lli> n(4);
	cin>>n[0]>>n[1]>>n[2]>>n[3];
	sort (n.begin(), n.end());
	lli suma1,suma2;
	suma1=n[0]+n[3];
	suma2=n[1]+n[2];
	lli suma3=n[0]+n[1]+n[2];
	if ((suma1==suma2)or(suma3==n[3]))
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}
	
	return 0;
}
