#include <bits/stdc++.h>
#define lli long long int
using namespace std;


void funcion()
{
	lli n, diff, aux, primero, ultimo;
	cin>>n>>diff;
	set<lli> orden;
	set<lli>::iterator itr;
	for (int i=0; i<n; i++)
	{
		cin>>aux;
		orden.insert(aux);
	}
	itr=orden.begin();
	primero=*itr;
	itr=orden.end();
	itr--;
	ultimo=*itr;
	lli l,r;
	if((primero+ultimo)%2==0)
	{
		lli mitad=(primero+ultimo)/2;
		l=abs(mitad-primero);
		r=abs(mitad-ultimo);
		if ((diff<l)or(diff<r))
		{
			cout<<"-1\n";
			return;
		}
		else
		{
			primero+=diff;
			cout<<primero<<endl;
			return;
		}
	}
	
	else
	{
		lli mitad = (primero+ultimo+1)/2;
		l=abs(mitad-primero);
		r=abs(mitad-ultimo);
		if ((diff<l)or(diff<r))
		{
			cout<<"-1\n";
			return;
		}
		else
		{
			primero+=diff;
			cout<<primero<<endl;
		}
		
	}
	
	return;
}




int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli q;
	cin>>q;
	for(int i=0; i<q; i++)
	{
		funcion();
	}
	return 0;
}

