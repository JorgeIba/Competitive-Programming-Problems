#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void funcion()
{
	lli n,m, div=0, resi=0, suma=0;
	cin>>n>>m;
	vector<lli> multi(10);
	
	for (int i=0; i<10; i++)
	{
		suma+=(m*i)%10;
		multi[i]=suma;
	}
	
	div= n/(m*10);
	lli res=0;
	resi= n/(m);
	resi=resi%10;
	//cout<<resi<<endl;
	if (div>=1)
	{
		res=div*(suma);
		//cout<<res<<endl;
	}
	res+=(multi[resi]);
	
	cout<<res<<endl;
	
	
}



int main()
{
	lli t;
	cin>>t;
	for (int i=0; i<t; i++)
	{
		funcion();
	}
	return 0;
}
