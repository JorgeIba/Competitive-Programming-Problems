#include <bits/stdc++.h>

#define lli __int128
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
			m = (__int128) m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

ll gcd(ll a, ll b)
{
    return __gcd(a, b);
}

lli mul(lli a, lli b, lli mod)
{
    lli res = 0;
    a = (a)%mod;
    while(b)
    {
        if(b&1) res = (a+res)%mod;
        b>>=1;
        a = (a+a)%mod;
    }
    return res;
}

lli getFactor(lli n){
	lli a = rand()%(n-1) + 1 , b = rand()%(n-1) + 1;
	lli x = 2, y = 2, d = 1;
	while(d == 1){
        x = x*(x+b)%n + a;
        y = y*(y+b)%n + a;
        y = y*(y+b)%n + a;
		d = gcd(abs ((ll)x - (ll)y), n);
	}
	return d;
}

vector< ll > fact;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
	}
	if(n > 1) fact.push_back(n);
}

void solve()
{
    ll n; cin>>n;
    factorizePollardRho(n);
    string s;
    lli howMuch = SZ(fact);
    sort(all(fact));
    for(ll i = 0; i<howMuch; i++)
    {
        cout << fact[i];
        if(i != (howMuch - 1))
        {
            cout << " ";
        }
    }
    cout << endl;
}

int main () {
	fastIO();
    ll t; cin>>t;
    while(t--) solve();
	return 0;
}