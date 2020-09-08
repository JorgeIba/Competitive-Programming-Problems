#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n, contador=0;
	cin>>n;
	if (n<4)
	{
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	
	if (n%2==1)
	{
		for (int i=n; i>5; i=i-2)
		{
			contador++;
			cout<<i<<" - "<<i-1<<" = 1"<<endl;
		}
		cout<<"5 * 3 = 15\n";
		cout<<"2 * 4 = 8\n";
		cout<<"15 + 8 = 23\n";
		cout<<"23 + 1 = 24\n";
		for (int i=0; i<contador; i++)
		{
			cout<<"24 * 1 = 24\n";
		}
	}
	else
	{
		for (int i=n; i>4; i=i-2)
		{
			contador++;
			cout<<i<<" - "<<i-1<<" = 1\n";
		}
		cout<<"4 * 3 = 12\n";
		cout<<"2 * 12 = 24\n";
		cout<<"1 * 24 = 24\n";
		for (int i=0; i<contador; i++)
		{
			cout<<"1 * 24 = 24\n";
		}
	}
	return 0;
}
