#include <bits/stdc++.h>
using namespace std;

#define lli long long int

int main()
{
	set<lli> ints;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli cantidad, enteros=0;
	double numeros, decimales=0;
	vector<lli> res;
	
	cin>>cantidad;
	for (lli i=0; i<cantidad; i++)
	{
		cin>>numeros;
		enteros+=floor(numeros);
		if ((abs(floor(numeros))-abs(numeros))==0)
		{
			ints.insert(i);
		}
		res.push_back(floor(numeros));
	}
	
	if (enteros==0)
	{
		for (lli i=0; i<cantidad; i++)
		{
			cout<<res[i]<<endl;
		}
	}
	else
	{
		for (lli i=0; i<cantidad; i++)
		{
			if (((enteros)<0)and(ints.find(i)==ints.end()))
			{
				enteros++;
				res[i]++;
			}
			cout<<res[i]<<endl;
		}
	}
	return 0;
}
