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
	lli auxF, auxS;
	lli tamano=numerosN.size();
	vector< pair<lli, lli> > exigencia(tamano);
	bool flag=false;
	
	if (numerosN.size()==1)
	{
		if (rating >= numerosN[0].first)
		{
			return true;
		}
	}
	
	for (int i=0; i<numerosN.size(); i++)
	{
		auxF=numerosN[i].first;
		auxS=numerosN[i].second;
		exigencia[i].first=auxF+auxS;
		exigencia[i].second=i;
	}
	
	sort(exigencia.rbegin(), exigencia.rend());
	lli aux, contador=0;
	for(int i=0; i<exigencia.size(); i++)
	{
		aux=exigencia[i].second;
		if (rating >= numerosN[aux].first)
		{
			rating+=numerosN[aux].second;
			contador++;
		}
		else
		{
			return false;
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
