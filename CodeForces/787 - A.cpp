#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	lli a,b,c,d;
	cin>>a>>b>>c>>d;
	if(b == d)
	{
		cout<<b<<endl;
		return 0;
	}
	
	for (int i=0; i<=100000; i++)
	{
		if (((( ( ( (d-b) + (c * i) )%a) == 0) and (( (d-b) + (c * i) ) >=0  ))))
		{
			//cout<<i<<endl;
			cout<<(lli)(i*c + d)<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
