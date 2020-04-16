#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli CeilIndex( vector<lli> tailIndex, lli buscar, lli r)
{
	lli l=0;
	lli res=0;
	while(l<=r)
	{
		lli posible = l + (r-l)/2;
		if ( buscar <= numeros[ tailIndex[posible] ]  )
		{
			res = posible;
			r = posible-1;
		}
		else
		{
			l = posible + 1;
		}	
	}
	
	return res;
}



void LIS(vector<lli> numeros; ,lli n)
{
	vector<lli> tailIndex(n,0);
	vector<lli> prevIndex(n,-1);
	
	lli ultimo=0;
	
	for (int i=1; i<n; i++)
	{
		if (numeros[i] <= numeros[tailIndex[0]])
		{
			tailIndex[0] = i;
		}
		else if (numeros[i] >= numeros[tailIndex[ultimo]])
		{
			prevIndex[i] = tailIndex[ultimo];
			ultimo++;
			tailIndex[ultimo] = i;
			
		}
		else
		{
			lli index = CeilIndex( tailIndex, numeros[i], ultimo);
			prevIndex[i] = tailIndex[index-1];
			tailIndex[index] = i;
		}
	}
	
	stack<lli> pila;
	lli x=tailIndex[ultimo];
	while(x!=-1)
	{
		pila.push(numeros[x]);
		x = prevIndex[x];
	}	
	while(!pila.empty())
	{
		cout<<pila.top()<<endl;
		pila.pop();
	}	
}




int main()
{
	lli n;
	cin>>n;
	numeros.resize(n,0);
	for (int i=0; i<n; i++)
	{
		cin>>numeros[i];
	}
	LIS(numeros,n);
	
	return 0;
}
