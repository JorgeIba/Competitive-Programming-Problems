#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	long int w,h,x,y;
	bool flag=false;
	cin>>w>>h>>x>>y;
	if ((x*2==w)and(y*2==h))
	{
		flag=true;
	}
	cout<<fixed<<setprecision(10)<<((w*h)/2)<<" ";
	flag?cout<<1<<endl:cout<<0<<endl;
	return 0;
}
