#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	lli n; cin>>n;
	vector<lli> numeros(n);
	for(auto &x: numeros)
	{
		cin>>x;
	}
	lli aux = 1;
	lli lcm = 1;
	for(int i=0; i<n; i++)
	{
		lcm = (lcm * numeros[i]) / (__gcd(lcm, numeros[i]));
	}
	cout<<lcm<<endl;


	return 0;
}