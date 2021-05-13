#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a*a % mod;
    }
    return res;
}


const lli MOD = 1e9+7;
const lli maxK = 1e3+10;
vector<lli> fact(maxK), invFact(maxK);

void prec()
{
    fact[0] = invFact[0] = 1;
    for(lli i = 1; i < maxK; i++)
    {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = binPow(fact[i], MOD-2, MOD);
    }
}

lli nCr(lli n, lli r)
{
    if(r < 0 || r > n) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}


int main () {
	//fastIO();
    prec();
    lli n, k; cin>>n>>k;
    lli ans = fact[n];
    for(lli ki = 1; ki <= k; ki++)
    {
        if(n-ki <= 0) break;
        lli cuantos = 0;
        
        cuantos = nCr(k, ki) * fact[n-ki] % MOD;
        
        if(ki % 2 == 0) ans += cuantos;
        else ans -= cuantos;

        if( ans >= MOD) ans -= MOD;
        else if(ans < 0) ans += MOD;

    }

    cout << ans << endl;

	return 0;
}