#include <bits/stdc++.h>
using namespace std;

int main()
{
	int l,r, res=0, exor;
	cin>>l>>r;
	
	for(int i=l; i<=r; i++)
	{
		for (int j=i; j<=r; j++)
		{
			exor=(j^i);
			res=max(res,exor);
		}
	}
	cout<<res<<endl;
	return 0;
}
