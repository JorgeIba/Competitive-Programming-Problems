#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector< pair<lli,lli> > descomp;

void solve(lli n)
{
	lli cont=0;
	while(n%2==0)
	{
		cont++;
		n/=2;
	}
	if(cont)
	{
		descomp.emplace_back(2,cont);
	}
	
	for(lli i=3; i*i<=n; i+=2)
	{
		if(n%i==0)
		{
			cont=0;
			while(n%i==0)
			{
				cont++;
				n/=i;
			}
			descomp.emplace_back(i, cont);
		}
	}
	
	if(n>1)
	{
		descomp.emplace_back(n,1);
	}
	
}


int main()
{
	lli n;
	cin>>n;
	solve(n);
	if(n==1)
	{
		cout<<1<<endl;
		return 0;
	}
	if(descomp.size() > 1)
	{
		cout<<1<<endl;
	}
	else
	{
		cout<<descomp[0].first<<endl;
	}
	
	return 0;
}
