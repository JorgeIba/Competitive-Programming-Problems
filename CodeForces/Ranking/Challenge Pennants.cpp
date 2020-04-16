#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	lli cinco = (n+4)*(n+3)*(n+2)*(n+1)*(n) / 120;
	lli tres = (n+2)*(n+1)*(n) / 6;
	cout<<(lli)(cinco*tres)<<endl;
	
	return 0;
}
