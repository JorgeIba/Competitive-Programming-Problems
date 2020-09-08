#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	bool flag=false;
	lli n, contador=0, contadoraux=0;
	string aux;
	cin>>n;
	vector< vector<lli> > avr(n);
	for (lli i=0; i<n; i++)
	{
		cin>>aux;
		for (int j=0; j<10; j++)
		{
			avr[i].push_back(aux[j]-97);	
		}
	}
	
	for (lli i=0; i<n; i++)
	{
		sort(avr[i].begin(), avr[i].end());
	}
	
	sort(avr.begin(), avr.end());
	
	for (lli i=1; i<n; i++)
	{
		for (int j=0; j<10; j++)
		{
			if (avr[i-1][j]==avr[i][j])
			{
				flag=true;
				continue;
			}
			else
			{
				flag=false;
				break;
			}
		}
		if ((flag)and(i==n-1))
		{
			contador++;
			contadoraux+=(contador)*(contador+1)/2;
		}
		if (flag)
		{
			contador++;
			flag=false;
		}
		else if (flag==false)
		{
			contadoraux+=(contador)*(contador+1)/2;	
			contador=0;
		}
	}
	
	cout<<contadoraux<<endl;
	
	return 0;
}
