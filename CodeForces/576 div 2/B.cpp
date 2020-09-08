#include <bits/stdc++.h>
#define lli long long int
#define ld long double
using namespace std;

int main()
{
	lli h,l;
	cin>>h>>l;
	lli c=h*h + l*l;
	cout<<fixed<<setprecision(13)<< (ld)(c)/(2*h) - h <<endl;
	
	return 0;
}
