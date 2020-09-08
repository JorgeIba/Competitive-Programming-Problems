#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
lli a,b,x,y;
bool check(lli posible)
{
	if((posible * x <= a)and(posible * y <= b))
	{
		return true;
	}
	return false;
}
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); 
	cin>>a>>b>>x>>y;
	lli gcd=__gcd(x,y);
	x/=gcd;
	y/=gcd;
	lli l=0,r=100000000;
	lli posible=0, res=0;
	while(l<=r)
	{
		posible= l + (r-l)/2;
		if (check(posible))
		{
			l=posible+1;
			res=posible;
		}
		else
		{
			r=posible-1;
		}
	}
	cout<<res*x<<" "<<res*y<<endl;
	return 0;
}
