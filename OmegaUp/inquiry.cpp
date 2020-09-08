#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	lli n;
	cin>>n;
	vector<lli> numeros(n);
	lli suma=0;
	for(int i=0; i<n; i++)
	{
		cin>>numeros[i];
		suma+=numeros[i];
	}
	
	lli cuadrados=0;
	lli maximo=0;
	for(int i=0; i<n-1; i++)
	{
		cuadrados+= pow(numeros[i],2);
		suma-=numeros[i];
		maximo=max(maximo,cuadrados*suma);
//		cout<<cuadrados*suma<<endl;		
	}
	cout<<maximo<<endl;
		
	return 0;
}
