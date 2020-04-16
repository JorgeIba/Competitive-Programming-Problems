#include <bits/stdc++.h>
#define lli long long int
 
using namespace std;
 
 
int main()
{
	lli a, b;
	cin>>a>>b;
	lli aux = min(a,b);
	b = max(a,b);
	a = aux;
 
	lli resta = b-a;
 
	vector<lli> divisores;
 
	for(lli i=1; i*i <= resta; i++)
	{
		if(resta%i==0)
		{
			if( i*i == resta)
			{
				divisores.push_back(i);
			}
			else
			{
				divisores.push_back(i);
				divisores.push_back(resta/i);
			}
		}
	}
 
	lli minimo = 1000000000000000LL;
	lli kGanador=0;
	lli k=0;
	//cout<<a<<" "<<b<<endl;
	for(auto divisor: divisores)
	{
		lli lcm = 0;
		//cout<<"divisor "<<divisor<<endl;
		if ( ( a%divisor ==0 ) and (b%divisor == 0))
		{
			lcm = a*b/divisor;
			k=0;
			//cout<<"Entre aqui\n";
		}
		else
		{
			lli division1 = a/divisor;
			division1 = divisor*(division1+1);
			k = division1 - a;
			lcm = (a+k)*(b+k)/divisor;
		}
		//cout<<lcm<<endl;
		if(lcm <= minimo)
		{
			minimo = lcm;
			kGanador = k;
		}
	}
 
	cout<<kGanador<<endl;
 
 
	return 0;
}
