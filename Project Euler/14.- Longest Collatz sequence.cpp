#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int dp[1000010];

lli funcion(lli n)
{
	lli no=0, si=0;
	if (n==1)
	{
		return 0;
	}
	if ((n<=1000010)and(dp[n]!=-1))
	{
		return dp[n];	
	}
	
	if(n%2==0)
	{
		si = funcion(n/2) + 1;
	}
	else
	{
		no = funcion (3*n + 1) + 1;
	}
	
	if (n<=1000010)
	{
		return dp[n] = max(si,no);	
	}
	else
	{
		return max(si,no);	
	}	
}
int main()
{
	memset(dp,-1,sizeof(dp));
	lli maxi=0, indice =-1;
	for (int i=500000; i<1000000; i++)
	{
		lli res=funcion(i);
		if (res > maxi)
		{
			maxi = res;
			indice = i;
		}
	}
	cout<<indice<<" "<<maxi<<endl;
	return 0;
}


