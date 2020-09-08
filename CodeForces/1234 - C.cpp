#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int funcion()
{
	lli n;
	cin>>n;
	string r1;
	string r2;
	cin>>r1>>r2;
	bool flag = false; //False arriba, true abajo

	lli contador=0;
	for (int i=0; i<n; i++)
	{
		if (	((r1[i] != '1')and(r1[i] != '2'))	and		( ((r2[i] != '1')and(r2[i] != '2' )) )	)
		{
				contador++;
				flag = !flag;
		}
		
		if ((	((r1[i] == '1')or(r1[i] == '2'))	and		( ((r2[i] != '1')and(r2[i] != '2' )) )	) and (flag==true))
		{
			cout<<"NO\n";
			return 0;
		}
		if ((	((r1[i] != '1')and(r1[i] != '2'))	and		( ((r2[i] == '1')or(r2[i] == '2' )) )	) and (flag==false ))
		{
			cout<<"NO\n";
			return 0;
		}
	}
	if (contador%2==1)
	{
		//cout<<contador<<endl;
		cout<<"YES\n";
		return 0;
	}
	else
	{
		cout<<"NO\n";
		return 0;
	}
	
	return 0;
}

int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//cout.tie(0);
	lli q;
	cin>>q;
	while(q--)
	{
		funcion();
	}
	return 0;
}
