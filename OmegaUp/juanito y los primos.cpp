#include <bits/stdc++.h>
using namespace std;

int main ()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	long long unsigned int n=0;
	cin>>n;	
	if ((n==2)or(n==3))
	{
		cout<<"si es primo";
		return 0;
	}
	else if (n==1)
	{
		cout<<"no es primo";
		return 0;
	}
	if ((n%2==0)or(n%3==0))
	{
		cout<<"no es primo";
		return 0;
	}
	for (long long unsigned int i=5; i*i<=n; i=i+6)
	{
		if ((n%i==0)or(n%(i+2)==0))
		{
			cout<<"no es primo";
			return 0;
		}
	}
	cout<<"si es primo";
	return 0;
}
