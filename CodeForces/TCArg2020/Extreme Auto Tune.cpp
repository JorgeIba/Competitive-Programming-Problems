#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
const lli MOD = 998244353, maxK = 25005;

vector< lli > B(maxK), fact(maxK), ifact(maxK);

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
    B[0] = fact[0] = ifact[0] = 1; 

    for(int i = 1; i<maxK; i++)
    {
        fact[i] = (i*fact[i-1])%MOD;
        ifact[i] = binPow(fact[i], MOD-2, MOD);
    }
    for(int i = 1; i < maxK; i++)
    {
        lli aux = 0;
        for(int k = 0; k<=i-1; k++)
        {
            lli inv = binPow(i-k+1, MOD-2, MOD);
            aux = (aux + (((nChoosek(i, k) * B[k])%MOD)*inv)%MOD)%MOD;
        }
        B[i] = (1 - aux + MOD)%MOD;
        //if(B[i] < 0) B[i] += MOD;
    }
}


int main()
{
    //fastIO();
    prec();
    lli m, p; cin>>m>>p;
    while(m--)
    {
        lli n; cin>>n;
        lli suma = 0;
        n = n % MOD;
        for(int k = 0; k<=p; k++)
        {
            suma = (suma + ((nChoosek(p+1, k) * B[k])%MOD) * binPow(n, p + 1 - k, MOD))%MOD;
        }
        lli res = (suma * binPow(p+1, MOD-2, MOD))%MOD;
        assert(res >= 0 && res < MOD);
        cout << res << endl;
    }
    return 0;
}