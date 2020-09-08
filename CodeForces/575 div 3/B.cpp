#include <bits/stdc++.h>
#define lli long long int
using namespace std;


vector<lli> pos;

bool funcion(lli tamano, lli target)
{
	lli contador=0, aux, contador2=0;
	
	for (lli i=1; i<=tamano; i++)
	{
		cin>>aux;
		if ((aux%2==1)and(contador!=target-1))
		{
			contador++;
			pos.push_back(i);
		}
		else if ((contador==target-1)and(aux%2==1))
		{
			contador2++;		
		}
	}

	
	if ((contador+contador2)<target)
	{
		return false;
	}
	else if ((contador+contador2)==target)
	{
		return true;
	}
	else
	{
		if ((contador2)%2==1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli q, tamano, target;
	cin>>q;
	for (int i=0; i<q; i++)
	{
		pos.clear();
		cin>>tamano>>target;
		if (funcion(tamano, target))
		{
			cout<<"YES\n";
			for (int i=0; i<pos.size(); i++)
			{
				cout<<pos[i]<<" ";
			}
			cout<<tamano<<endl;
		}
		else
		{
			cout<<"NO\n";
		}
	}
	return 0;
}
