#include <bits/stdc++.h>
#define lli long long int
using namespace std;



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n;
	cin>>n;
	lli array[n][n];
	for (lli i=0; i<n; i++)
	{
		for (lli j=0; j<n; j++)
		{
			cin>>array[i][j];
		}
	}
	
	lli a = sqrt( array[0][1]*array[0][2]/array[1][2]  );
	
	cout<<a<<" ";
	for (lli i=1; i<n; i++)
	{
		cout<< (lli)((array[0][i])/a)<<" ";
	}
	
	
	return 0;
}
