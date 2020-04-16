#include <bits/stdc++.h>
#define lli long long int
#define ld long double
using namespace std;

int main()
{
	lli a,b,c,d;
	cin>>a>>b>>c>>d;
	ld p1 = (double) a/b ;
	ld q1 = (double) 1 - p1;
	ld p2 = (double) c/d;
	ld q2 = (double) 1 - p2;
	
	cout<<fixed<<setprecision(15)<<(p1 / (1 - q1*q2))<<endl;

	return 0;
}
