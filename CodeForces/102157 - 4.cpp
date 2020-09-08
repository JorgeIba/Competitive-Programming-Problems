#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	string s;
	lli contador=0;
	for (int i=0; i<n; i++)
	{
		cin>>s;
		if (s=="left")
		{
			contador+= 270;
		}
		else if (s=="right")
		{
			contador+=90;
		}
		else if (s=="back")
		{
			contador+=180;
		}
	}
	
	if (contador%360==0)
	{
		cout<<"north\n";
	}
	else if (contador%360 == 90)
	{
		cout<<"east\n";
	}
	else if (contador%360==180)
	{
		cout<<"south\n";
	}
	else if (contador%360==270)
	{
		cout<<"west\n";
	}
	
	
	return 0;
}
