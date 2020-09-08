#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
vector<int> cuts(3);
lli dp[4][4005];
lli funcion(int indice, int n)
{	
	if (indice>=3)
	{
		return -100000;
	}
	if (n==0)
	{
		return 1;
	}
	if (n<0)
	{
		return -100000;
	}
	if(dp[indice][n]!=-1)
	{
		return dp[indice][n];
	}
	
	lli si = funcion(indice, n-cuts[indice]) + 1;
	lli no = funcion(indice+1, n);
	
	return dp[indice][n]=max(si,no);
}
 
 
 
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	memset(dp, -1, sizeof(dp));
	lli n;
	cin>>n>>cuts[0]>>cuts[1]>>cuts[2];
	//sort(cuts.begin(), cuts.end());
	cout<<funcion(0, n)-1<<endl;
	
	return 0;
}
