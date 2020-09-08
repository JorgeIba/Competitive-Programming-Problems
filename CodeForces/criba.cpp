#include <bits/stdc++.h>
#define lli long long unsigned int
using namespace std;

bool primos[2000010];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n;
	cin>>n;
		for (lli i=2; i*i<=n; i++)
		{
			if(primos[i]!=true)
			{
				for (lli j=2; i*j<=n; j++)
				{
					primos[i*j] = true;
				}
			}
		}
	lli suma=0;
	for (lli i=2; i<= n; i++)
	{
		if(primos[i]==false)
		{
			//cout<<i<<" ";
			suma+=i;
		}
	}
	cout<<suma;
	return 0;
}
