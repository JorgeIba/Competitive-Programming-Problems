#include <bits/stdc++.h>
using namespace std;

int main()
{
	long int pascal[51][51];
	
	for (long int i=1; i<51; i++)
	{
		pascal[i][1]=1;
	}
	
	for (long int i=1; i<51; i++)
	{
		for (int j=1; j<51; j++)
		{
			if (i==j)
			{
				pascal[i][j]=1;
			}
			else
			{
				if (pascal[i][j]==0)
				{
					pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
				}
			}
		}
	}
	
	for (int x=0; x<51; x++)
	{
		for(int y=0; y!=x; y++)
		{
			cout<<pascal[x][y]<<" ";
		}
		cout<<endl;
	}
	
	return 0;
}
