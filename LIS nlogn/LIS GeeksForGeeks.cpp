#include <bits/stdc++.h>
#define lli long long int
using namespace std;

vector<lli> numeros;

lli CeilIndex(lli r, vector<lli> tail, lli numero)
{
	
	lli l=0, res=0;
	while (l<=r)
	{
		lli posible = l + (r-l)/2;
		if (numero <= tail[posible])
		{
			res = posible;
			r = posible - 1;
		}
		else
		{
			l = posible + 1;
		}
	}
	return res;
}
lli LIS()
{
	vector<lli> tail(numeros.size(),0);
	tail[0]=numeros[0];
	lli ultimo=0;
	for (lli i=1; i<numeros.size(); i++)
	{
		if (numeros[i] <= tail[0])
		{
			tail[0] = numeros[i];
		}
		else if (numeros[i] > tail[ultimo] )
		{
			ultimo ++;
			tail[ultimo] = numeros[i];
		}
		else 
		{
			lli index = CeilIndex(ultimo, tail, numeros[i]);
			tail[index] = numeros[i];
		}
	}
	return ultimo+1;
}

void funcion()
{
	lli n;
	cin>>n;
	numeros.resize(n,0);
	for (int i=0; i<n; i++)
	{
		cin>>numeros[i];
	}
	cout<<LIS()<<endl;
}

int main()
{
	lli q;
	cin>>q;
	while(q--)
	{
		funcion();
	}
	return 0;
}
