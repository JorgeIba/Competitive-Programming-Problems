#include <bits/stdc++.h>
//#include <windows.h>
#define lli long long unsigned int
using namespace std;

int main()
{
	lli a,b;
	cin>>a>>b;
	while( a!=0 and b!=0 and (b>=2*a or a>=2*b)  )
	{
		lli divA = a/b;
		lli divB = b/a;
		lli resiA= a%b;
		lli resiB= b%a;
		if ((divA>0)and(divA%2==1))
		{
			a = b + resiA;
		}
		else if ((divA>0)and(divA%2==0))
		{
			a = resiA;
		}
		if ((divB>0)and(divB%2==1))
		{
			b = a + resiB;
		}
		else if ((divB>0)and(divB%2==0))
		{
			b = resiB;
		}
//		cout<<a<<" "<<b<<endl;
//		Sleep(1000);
	}
	
	cout<<a<<" "<<b<<endl;
	
	
	return 0;
}
