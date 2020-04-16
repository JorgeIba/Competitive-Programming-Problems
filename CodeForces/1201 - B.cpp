#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n, impar=0, aux, maxi=0, suma=0 ;
	cin>>n;
	for (lli i=0; i<n; i++)
	{
		cin>>aux;
		maxi=max(maxi, aux);
		suma+=aux;
		if ((aux%2ll)!=0)
		{
			impar++;
		}
	}
	
	suma=suma-maxi;
	//cout<<impar<<" "<<suma<<endl;
	if (((impar%2ll)==0)and(suma>=maxi))
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}
	return 0;
}
