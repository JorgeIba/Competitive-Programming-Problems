#include <bits/stdc++.h>
using namespace std;

bool testPrimality(int n)
{
	if (n<=1) return false;
	if (n<=3) return true;
	
	if((n%2==0)or(n%3==0))
	{
		return false;
	}
	
	for (int i=5; i*i<n; i=i+6)
	{
		if((n%i==0)or(n%(i+2)==0))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int n=0;
	cin>>n;
	if (testPrimality(n-2))
	{
		cout<<2<<" "<<n-2<<endl;
	}
	else
	{
		cout<<-1<<endl;
	}
}
