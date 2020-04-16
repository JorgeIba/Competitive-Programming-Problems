#include <bits/stdc++.h>
#define lli long long int
 
using namespace std;
 
void solve()
{
	lli n;
	cin>>n;
	lli arreglo[3];
	memset(arreglo, 0, sizeof(arreglo));
	for(int i=0; i<n; i++)
	{
		lli aux;
		cin>>aux;
		arreglo[ aux%3  ]++;
	}
	
	lli ans = arreglo[0];
	lli minimo = min(arreglo[1], arreglo[2]);
	if((arreglo[1]>0)and(arreglo[2]>0))
	{
		ans+=minimo;
		arreglo[1]-=minimo;
		arreglo[2]-=minimo;
	}
	ans+= arreglo[1]/3 + arreglo[2]/3;
	cout<<ans<<endl;
	
	
	
	
}
 
 
 
int main()
{
	lli t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
