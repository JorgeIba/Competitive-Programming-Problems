#include <bits/stdc++.h>

#define lli long long int
#define ll long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

lli powerMod(lli a, lli b, lli mod)
{
    lli res = 1;
    a = (a)%mod;
    while(b)
    {
        if(b&1) res = (a*res)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}

bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

lli gcd(lli a, lli b)
{
    return __gcd(a, b);
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll aleatorio(ll a, ll b){
	std::uniform_int_distribution<ll> dist(a, b);
	return dist(rng);
}

lli getFactor(lli n){
	lli a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = gcd(abs ((ll)x - (ll)y) , n);
	}
	return d;
}

map<lli, int> fact;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = (a*res);
        b>>=1;
        a = a*a;
    }
    return res;
}

lli sumPrime(lli p, lli a)
{
    return (binPow(p, a+1) - 1) / (p-1);
}

void solve()
{
    ll n; cin>>n;
    factorizePollardRho(n);
    lli suma = 1;
    bool pasarme = false;
    for(auto x: fact)
    {
        if(suma < 0 || suma > n) pasarme = true;
        suma *= sumPrime(x.first, x.second);
    }
    if(pasarme)
    {
        cout << "abundant\n";
        return;
    }
    suma -= n;
    if(suma < n)
    {
        cout << "deficient\n";
    }
    else if(suma == n)
    {
        cout << "perfect\n";
    }
    else
    {
        cout << "abundant\n";
    }
    
}

lli maxN = 1e12, sqrtmaxN = 1e6 + 100;

int main () {
	fastIO();
    //lowestPrimeSieve(sqrtmaxN);
    ll t; cin>>t;
    while(t--) solve();

	return 0;
}