#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}

lli binPow(lli a, lli b)
{
	lli res = 1;
	while(b)
	{
		if(b&1) res = (res*a)%MOD;
		b>>=1;
		a = (a*a)%MOD;
	}
	return res;
}

lli inverse;


lli pi_0(lli N){
	int m = sqrt(N);
	vector<lli> lo(m+1), hi(m+1), values;
	auto at = [&](lli x) -> lli&{
		if(x <= m) return lo[x];
		return hi[N / x];
	};
	for(int i = 1; i <= m; ++i){
		values.push_back(i);
		if(N / i != i) values.push_back(N / i);
	}
	sort(all(values), greater<lli>());
	for(lli n : values){
		lli a = n%MOD;
		at(n) = ((((((a * (a+1))%MOD) * (2*a + 1))%MOD) * inverse)%MOD - 1);
		if(at(n) < 0)
		{
			at(n) += MOD;
		}
	}
	
	//for(lli p = 2; p <= m; ++p)
	for(lli p: primes)
	{
		//if(at(p) == at(p - 1)) continue;
		if(p>m) break;
		lli mult = p*p;
		lli pk = (mult)%MOD;
		for(lli n : values){
			if(n < mult) break;
			lli aux = at(n/p) - at(p-1); if(aux < 0) aux+=MOD;
			aux = (aux*pk)%MOD;
			at(n) = (at(n) - aux);
			//at(n) = (at(n) - ((pk*( ((at(n / p) - at(p - 1))%MOD) ))%MOD))%MOD;
			if(at(n) < 0)
			{
				at(n) += MOD;
			}
		}
	}
	return at(N);
}


int main()
{
    fastIO();
    lli n;
	primesSieve(316228);
	inverse = binPow(6, MOD-2);
    while(cin>>n)
		cout<<pi_0(n)<<endl;


    return 0;
}