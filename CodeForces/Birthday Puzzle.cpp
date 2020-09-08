#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n;
	cin>>n;
	vector<lli> vec(n); //Vector donde estan los valores.
	for (lli i=0; i<n; i++)
	{
		cin>>vec[i];
	}
	lli a= pow(2,n) -1; //Todos los bits encendidos.
	lli x=a;
	lli suma=0, sumaAux;
	do
	{
		sumaAux=0;
		for (lli i=0; i<log2(x)+1; i++)
		{
			if (x&(1<<i))
			{
//				sumaAux= sumaAux|vec[i];
			}
		}
		x=(x-1)&a;
//		suma+=sumaAux;
	}while(x);
	
	cout<<suma<<endl;
	return 0;
}
