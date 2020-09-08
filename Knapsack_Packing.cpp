#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	map< lli, lli > numeros;
	lli n;
	cin>>n;
	lli power = pow(2,n);
	vector<lli> auxiliar(power);
	for(lli i=0; i<power; i++)
	{
		cin>>auxiliar[i];
		numeros[ auxiliar[i] ]++;
	}
	if(numeros[0]==0)
	{
		cout<<"impossible\n";
		return 0;
	}
	sort(auxiliar.begin(), auxiliar.end());
	
	for(lli i=1; i<power; i++)
	{
		if(numeros[ auxiliar[i] ] >0 )
		{
			for(lli j=i+1; j<power; j++)
			{
				if(numeros[ auxiliar[j] ] > 0)
				{
					numeros[ auxiliar[i] + auxiliar[j] ] --;	
				}
				
			}
		}
	}
	numeros[0]--;
	vector<lli> answer;
	for(auto x: numeros)
	{
		cout<<x.first<<" "<<x.second<<endl;
		if(x.second>0)
		{
			for(lli i=0; i<x.second; i++)
			{
				//cout<<x.first<<endl;
				answer.push_back(x.first);
			}
		}
	}
	
	if(answer.size()==n)
	{
		for(auto x:answer)
		{
			cout<<x<<endl;
		}
	}
	else
	{
		cout<<"impossible\n";
	}
	
	
	
	
	return 0;
}
