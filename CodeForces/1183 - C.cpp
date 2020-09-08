#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli n,k,a,b;

bool check(lli turnos)
{
	if((abs(a*turnos) + abs(k-turnos)*b)<n)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int funcion()
{
	cin>>n>>k>>a>>b;
	lli l=0, r=k, maxi=0;
	bool flag=false;
	while(l<=r)
	{
		lli posible=l + (r-l)/2;
		if (check(posible))
		{
			maxi=max(posible,maxi);
			l=posible + 1;
			flag=true;
		}
		else
		{
			r=posible-1;
		}
	}
	if (flag)
	{
		cout<<maxi<<endl;
	}
	else
	{
		cout<<-1<<endl;
	}
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli t;
	cin>>t;
	while(t--)
	{
		funcion();
	}
	return 0;
}
