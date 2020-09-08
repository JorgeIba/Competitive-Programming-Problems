#include <bits/stdc++.h>
#define ld long double
#define lli long long int
#define PI 3.1415926535
using namespace std;
 
int main()
{
	ld n, len;;
	cin>>n>>len;
	ld seno = sin((double)(360/(2*n))*(PI/180.0));
	//cout<<seno<<endl;
	ld radio = len/(2*seno);
	ld res = PI*radio*radio;
	cout<<fixed<<setprecision(10)<<res<<endl;
	return 0;
}
