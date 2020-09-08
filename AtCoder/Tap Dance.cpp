#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	cin>>s;
	bool flag=true;
	for (int i=0; i<s.length(); i++)
	{
		if ((i+1)%2==0)
		{
			if (s[i]=='R')
			{
				cout<<"No\n";
				return 0;
			}
		}
		else
		{
			if(s[i]=='L')
			{
				cout<<"No\n";
				return 0;
			}
		}
	}
	cout<<"Yes\n";
	return 0;
}
