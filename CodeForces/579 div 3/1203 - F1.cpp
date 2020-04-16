#include <bits/stdc++.h>
#define lli long long int
#define ld long double
using namespace std;
 
 
vector< pair< lli, lli> > numerosP;
vector< pair< lli, lli> > numerosN;
 
lli contadorP=0;
 
 
bool checarPositivos(lli &rating)
{
	for (int i=0; i<numerosP.size(); i++)
	{
		if (numerosP[i].first <= rating)
		{
		//	cout<<numerosP[i].first<<" "<<numerosP[i].second<<" "<<rating<<endl;
			rating+=numerosP[i].second;
			numerosP.erase(numerosP.begin() + i);
			i=-1;
			contadorP++;
			continue;
		}
		//cout<<numerosP[i].first<<" "<<numerosP[i].second<<" "<<rating<<endl;
	}
	
	if (numerosP.size()==0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
 
 
bool funcionNegativos(lli rating)
{
	lli mejorIzq=0, mejorDer=0, auxPos=0, min=10000;
	bool flag=false;
	while (numerosN.size()!=0)
	{
		if (numerosN.size()==1)
		{
			if (rating >= numerosN[0].first)
			{
				return true;
			}
		}
		
		if (rating < numerosN[0].first)
		{
			return false;
		}
		
		mejorIzq=rating-numerosN[0].first;
		mejorDer=rating+numerosN[0].second;
		
		//cout<<"Mejores: "<<mejorIzq<<" "<<mejorDer<<endl;
		
		if (mejorDer>=mejorIzq)
		{
			rating+=numerosN[0].second;
			numerosN.erase(numerosN.begin());
		}
		
		else
		{
			min=(numerosN[1].second);
			
			for (int i=1; i<numerosN.size(); i++)
			{
				if (((numerosN[i].second)>=min)and(abs(numerosN[i].second)<=mejorIzq))
				{
					min=(numerosN[i].second);
					auxPos=i;
				}
			}
			
			//cout<< "Recorri: " << numerosN[auxPos].first <<" "<< min <<endl;
			rating+=min;
			numerosN.erase(numerosN.begin() + auxPos);
		}
	}
	
	
	return true;
}
 
 
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n, rating, sumaN=0, sumaP=0, mayor=0, aux1=0, aux2=0;
	cin>>n>>rating;
	
 
	
	if (rating>=0)
	{
		sumaP=rating;
	}
	else
	{
		sumaN=rating;
	}
	
	
	for (int i=0; i<n; i++)
	{
		cin>>aux1>>aux2;
		if (aux2>=0)
		{
			numerosP.push_back(make_pair(aux1,aux2));
		}
		
		else
		{
			numerosN.push_back(make_pair(aux1,aux2));
		}
		
		if (aux2>=0)
		{
			sumaP+=aux2;
		}
		else
		{
			sumaN+=aux2;
		}
		mayor=max(mayor, aux1);
	}
	sort(numerosP.begin(), numerosP.end());
	sort(numerosN.rbegin(), numerosN.rend());
 
	
	
	if (( (sumaP)+(sumaN) <0 )or(sumaP<mayor) or ((!checarPositivos(rating))))
	{
		cout<<"NO\n";
		return 0;
	}
	
	if (funcionNegativos(rating))
	{
		cout<<"YES\n";
		return 0;
	}
	else
	{
		cout<<"NO\n";
		return 0;
	}
 
 
 
	return 0;
}
