#include <bits/stdc+.h>
#define lli long long int
using namespace std;
lli MOD =998244353;


lli binPow(lli a, lli b)
{
	lli res=1;
	while(b)
	{
		if(b&1) res*=a%MOD;
		b>>1;
		a=a*a%MOD;
	}
	return res;
}



int main()
{
	
	lli w,h;
	cin>>w>>h;
	lli auxW = binPow(2, w-1);
	lli auxH = binPow(2, h-1);
	cout<<binPow(3,7);
	
	
	return 0;
}
