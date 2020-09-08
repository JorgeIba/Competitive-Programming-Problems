#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;

const lli MOD = 1e9 + 7, maxK = 1e3 + 10;;

vector< lli > fact(maxK), ifact(maxK);

lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    a = a%mod;
    while(b)
    {
        if(b&1) res = (res * a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}

lli nChoosek(lli n, lli k)
{
    return (((fact[n] * ifact[n-k])%MOD )* ifact[k])%MOD;
}

void prec()
{
    fact[0] = ifact[0] = 1;
    for(int i = 1; i<maxK; i++)
    {
        fact[i] = (i*fact[i-1])%MOD;
        ifact[i] = binPow(fact[i], MOD-2, MOD);
    }
}

lli dp[maxK];

lli fun(lli n, lli k)
{
    if(k == 0) return n;
    lli &res = dp[k];
    if(res != -1) return res;
    lli suma = 0;
    for(int j = 0; j<=k-1; j++)
    {
        suma = (suma + nChoosek(k+1, j) * fun(n, j))%MOD;
    }
    return res = ((binPow(n+1, k+1, MOD) - 1 - suma + 2*MOD)%MOD * binPow(k+1, MOD-2, MOD))%MOD;
}


void solve()
{
    lli n, k; cin>>n>>k;
    memset(dp, -1, sizeof(dp));
    cout << fun(n, k) << endl;
}


int main () {
	fastIO();
    prec();
    lli t; cin>>t;
    while(t--) solve();

	return 0;
}