#include <bits/stdc++.h>
#define lli long long int
using namespace std;


lli dp[30][30];
lli n;

lli calculate (lli row, lli column)
{
	lli down=0, right=0;
	if ((row==n-1)and(column==n-1))
	{
		return 1;
	}
	
	if ((row>=n)or(column>=n))
	{
		return 0;
	}
	if (dp[row][column]!=-1)
	{
		return dp[row][column];
	}
	if ((row!=n-1)and(column==n-1))
	{
		down = calculate(row+1, column);
	}
	else if ((row==n-1)and(column!=n-1))
	{
		right = calculate(row, column+1);
	}
	else
	{
		down = calculate(row+1, column);
		right = calculate(row, column+1);
	}
	
	return dp[row][column] = down+right;
	
}

int main()
{	
	int x; //Here you have to digit a 20;
	cin>>x;
	n = x+1;
	lli array[n][n];
	memset(dp, -1, sizeof(dp));
	cout<<calculate(0,0)<<endl;
	
	return 0;
}
