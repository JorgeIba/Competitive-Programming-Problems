#include <bits/stdc++.h>
#define lli long long unsigned int

using namespace std;


lli cuantosHay(lli limitInf, lli limitSup, lli numero)
{
	lli total= limitSup/numero - limitInf/numero;
	return total;
}


int main()
{
	lli a,b,c,d;
	cin>>a>>b>>c>>d;
	lli total=0, mcm;
	total=b-a+1;
	mcm=(c*d)/(__gcd(c,d));
	if ((a%c==0)or(a%d==0))
	{
		total--;
	}
	total= total - cuantosHay(a,b,c) - cuantosHay(a,b,d) + cuantosHay(a,b,mcm);
	cout<<total;
	return 0;
}
