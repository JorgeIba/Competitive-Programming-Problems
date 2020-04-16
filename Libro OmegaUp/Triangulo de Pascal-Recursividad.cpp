#include <bits/stdc++.h>
using namespace std;



int pasc[51][51];

int Pascal(int i, int j)
{
	if ((j==1)or(i==j))
	{
		pasc[i][j]=1;
		return 1;
	}
	if (pasc[i][j]!=0)
	{
		return pasc[i][j];
	}
	else
	{
		pasc[i][j]=Pascal(i-1,j-1) + Pascal(i-1, j);
		return pasc[i][j];
	}
	
	
}

int main()
{
	int i, j;
	cin>>i>>j;
	cout<<Pascal(i,j)<<endl;
	for (int x=0; x<51; x++)
	{
		for(int y=0; y!=x; y++)
		{
			cout<<pasc[x][y]<<" ";
		}
		cout<<endl;
	}
	
	return 0;
}
