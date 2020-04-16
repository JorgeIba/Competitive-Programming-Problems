#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli a=0,b=0,q=0, ref1=0, ref2=0, num1=0, num2=0, gcd=0, set1=0, set2=0;
	cin>>a>>b>>q;
	gcd=__gcd(a,b);
	bool flag=false;
	if (gcd==1)
	{
		flag=true;
	}
	a= (lli)  a/gcd;
	b= (lli)  b/gcd;
	for (lli i=0; i<q; i++)
	{
		cin>>ref1>>num1>>ref2>>num2;
		if(!flag)
		{
			
			if (ref1==1)
			{
				
				set1= (lli) ((num1-1)/a);
			}
			else if (ref1==2)
			{
				set1=(lli) ((num1-1)/b);
			}
			
			if (ref2==1)
			{
				set2= (lli) ((num2-1)/a);
			}
			
			else if (ref2==2)
			{
				set2=(lli) ((num2-1)/b);
			}
			
			if (set1==set2)
			{
				cout<<"YES\n";
			}
			else
			{
				cout<<"NO\n";
			}
		}
		
		
		else
		{
			cout<<"YES\n";
		}
	}
	return 0;
}
