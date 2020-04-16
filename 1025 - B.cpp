#include <bits/stdc++.h>
#define lli long long unsigned int
using namespace std;

vector<vector<int>> primeFactors;
void primeFactorsSieve(lli n){
	primeFactors.resize(n + 1);
	for(int i = 0; i < primes.size(); ++i){
		int p = primes[i];
		for(int j = p; j <= n; j += p)
			primeFactors[j].push_back(p);
	}
}


int main()
{
	int n;
	vector<lli> numeros;
	criba();
	for (int i=0; i<n; i++)
	{
		lli aux1,aux2;
		cin>>aux1>>aux2;
		numeros.push_back(aux1*aux2);
	}
	
	vector<vector<int>> answer = primeFactorsSieve(aux1*aux2);
	for(auto x: answer)
	{
		cout<<x<<" ";
	}
	
	
	
	return 0;
}
