#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define MAAX 10000000

int main()
{
	bool check[MAAX];
	lli n;
	cin>>n;
	memset(check, true, MAAX*sizeof(bool));	
	for (int i=2; i<MAAX; i++)
	{
		for (int j=2; i*j<MAAX; j++)
		{
			check[i*j]=false;
		}
	}
	
	cout<<1;
	
	return 0;
}
