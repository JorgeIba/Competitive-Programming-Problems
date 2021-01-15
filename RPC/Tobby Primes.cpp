#include <bits/stdc++.h>

#define i128 __int128
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

i128 powerMod(i128 a, i128 b, i128 mod)
{
    i128 res = 1;
    a = (a)%mod;
    while(b)
    {
        if(b&1) res = (a*res)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}

bool isPrimeMillerRabin(i128 n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	i128 d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		i128 m = powerMod(a, d, n);
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

lli gcd(lli a, lli b)
{
    return __gcd(a, b);
}

i128 mul(i128 a, i128 b, i128 mod)
{
    i128 res = 0;
    a = (a)%mod;
    while(b)
    {
        if(b&1) res = (a+res)%mod;
        b>>=1;
        a = (a+a)%mod;
    }
    return res;
}

i128 getFactor(i128 n){
	i128 a = rand()%(n-1) + 1 , b = rand()%(n-1) + 1;
	i128 x = 2, y = 2, d = 1;
	while(d == 1){
        x = x*(x+b)%n + a;
        y = y*(y+b)%n + a;
        y = y*(y+b)%n + a;
		d = gcd(abs ((lli)x - (lli)y), n);
	}
	return d;
}

vector< lli > fact;
void factorizePollardRho(i128 n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		i128 f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
	}
	if(n > 1) fact.push_back(n);
}

void solve()
{
    lli n; cin>>n;
    factorizePollardRho(n);
    string s;
    i128 howMuch = SZ(fact);
    sort(all(fact));
    for(lli i = 0; i<howMuch; i++)
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
    lli t; cin>>t;
    while(t--) solve();
	return 0;
}