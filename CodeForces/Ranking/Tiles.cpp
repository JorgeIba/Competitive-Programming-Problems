#include <bits/stdc++.h>
#define lli long long unsigned int
using namespace std;
lli MOD = 998244353;


lli binPow(lli a, lli b)
{
	lli res=1;
	while(b)
	{
		if(b&1)
		{
			res=(res*a)%MOD;	
		} 
		b>>=1;
		a=(a*a)%MOD;
		//cout<<b<<" "<<a<<endl;
	}
	return res;
}



int main()
{
	
	lli w,h;
	cin>>w>>h;
	lli auxW = binPow(2, w-1);
	lli auxH = binPow(2, h-1);
	lli res = auxW*auxH%MOD;
	res = 4*res%MOD;
	cout<<res<<endl;
	return 0;
}
