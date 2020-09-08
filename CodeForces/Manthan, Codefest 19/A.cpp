#include <bits/stdc++.h>
#define lli long long int
using namespace std;


lli solve[3];

void funcion()
{
	lli a, b, n;
	cin>>a>>b>>n;
	solve[0]=a;
	solve[1]=b;
	solve[2]=a^b;
	
	if (n%3==0)
	{
		cout<<solve[0]<<endl;
		return;
	}
	else if (n%3==1)
	{
		cout<<solve[1]<<endl;
		return;
	}
	else 
	{
		cout<<solve[2]<<endl;
	}
	return;
	
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli q;
	cin>>q;
	for (int i=0; i<q; i++)
	{
		funcion();
	}
	
	return 0;
}
