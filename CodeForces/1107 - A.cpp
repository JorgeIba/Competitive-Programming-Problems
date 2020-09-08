#include <bits/stdc++.h>
using namespace std;

void funcion()
{
	string n, tamano;
	cin>>tamano>>n;
	if (n.length()==2)
	{
		if (n[0]>=n[1])
		{
			cout<<"NO\n";
			return;
		}
	}	
	
	cout<<"YES\n"<<"2\n";
	
	cout<<n[0]<<" ";
	for (int i=1; i<n.length(); i++)
	{
		cout<<n[i];
	}
	cout<<endl;
	return;
}


int main()
{
	int q;	
	cin>>q;
	for(int i=0; i<q; i++)
	{
		funcion();
	}
	return 0;
}
