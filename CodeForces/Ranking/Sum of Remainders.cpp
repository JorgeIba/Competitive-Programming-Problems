#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n,m;
	cin>>n>>m;
	lli suma=0;
	lli t=n*m;
	for (lli i=1; i<=m; i++)
	{
		if(i>n)
		{
			break;
		}
		lli aux = n/i;
		suma+=aux*i;
		cout<<aux*i<<" <- i[n/i] \n";
		//cout<<suma<<" <- suma\n";
	}
	cout<<t-suma<<endl;
	 /*
	 cout<<"-----------------------\n";
	 suma=0;
	for(lli j=1; j<=n; j++)
	{
		cout<<"Para: "<<j<<" su suma:\n";
		for (lli i=1; i<=j; i++)
		{
			//cout<<j%i<<" ";
			suma+=j%i;
		}
		cout<<suma<<endl;
		suma=0;
	}
	*/
	
	
	return 0;
}
