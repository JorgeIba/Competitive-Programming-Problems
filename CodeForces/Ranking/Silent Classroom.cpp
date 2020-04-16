#include <bits/stdc++.h>
#define lli long long int

using namespace std;


lli Gauss(lli n)
{
	n-=1;
	lli sumaGauss=0;
	sumaGauss= n*(n+1)/2;
	return sumaGauss;
}

int main()
{
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	lli n;
	map<char, lli> conteo;
	cin>>n;
	for(int i=0; i<n; i++)
	{
		string aux;
		cin>>aux;
		conteo[aux[0]]++;
	}
	
	lli suma=0;
	for(auto x: conteo)
	{
		//cout<<x.first<<" "<<x.second<<endl;           
		if(x.second <=2)
		{
			continue;
		}
		
		if((x.second==3))
		{
			suma+=1;
			continue;
		}
		
		else
		{
			if(x.second % 2 == 0)
			{
				lli aux = Gauss(x.second/2);
				suma+=aux*2;
			}
			else
			{ 
				lli aux = Gauss(x.second/2);
				aux+= Gauss(x.second/2 + 1);
				suma+=aux;
			}
			
		}
	}
	cout<<suma<<endl;
	
	
	return 0;
}
