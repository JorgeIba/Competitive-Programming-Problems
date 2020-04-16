#include <bits/stdc++.h>
#define lli long long int
#define MOD 10000007

using namespace std;

vector<int> primes;
vector<bool> isPrime;
vector< int > descomposicion;

void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2)
	{
		if(isPrime[i])
		{
			primes.push_back(i);
			if(i <= limit)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


void descomponer(lli n)
{
	lli aux=0, piso=0;
	for(int i=0; i<primes.size(); i++)
	{
		lli primo = primes[i];
		if(primo > n)
		{
			break;
		}
		lli suma=0;
		int j=1;
		while(primo <= n)
		{
			aux = pow(primo,j);
			piso = n/aux;
			if(piso==0)
			{
				break;
			}
			suma+=piso;	
			j++;
		}
		if(suma>0)
		{
			descomposicion.push_back(suma);
		}
	}
}

lli Gauss(lli n)
{
	n=n%MOD;
	lli aux=(n)*(n+1)/2;
	return aux%MOD;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	primesSieve(1000000);
	lli n;
	lli res=1;
	while(true)
	{
		descomposicion.clear();
		cin>>n;
		if(n==0)
		{
			return 0;
		}
		descomponer(n);
		for(auto x: descomposicion)
		{
			res= (res*(Gauss(x+1)))%MOD;
		}
		cout<<res<<endl;
		res=1;
	}

	
	return 0;
}
