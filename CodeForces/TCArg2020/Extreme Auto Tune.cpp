#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > coeffs, fact, inverse;
const lli MOD = 998244353;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        b >>= 1;
        a = (a*a)%MOD;
    }
    return res;
}

void prec(lli k)
{
    coeffs.resize(25010);
    fact.resize(25010);
    inverse.resize(25010);

    fact[0] = 1;
    inverse[0] = 1;
    for(int i = 1; i<25000; i++)
    {
        fact[i] = (fact[i-1] * i) % MOD;
        inverse[i] = binPow( fact[i], MOD-2 );
    }
    for(int i = 0; i<=k; i++)
    {
        coeffs[i] = ((fact[k] * inverse[k-i])%MOD * inverse[i])%MOD;
    }
}


lli S(lli n, lli k)
{
    if(k == 0) return n;

    lli aux = (binPow(2, k+1) * n)%MOD;
    lli suma = 1;
    for(int i = 0; i<=k-1; i++)
    {
        //lli inverseCoeff = binPow(coeffs[i], MOD-2);
        suma = (suma + coeffs[i]*S(n, i))%MOD;
    }
    lli total = (aux - suma)%MOD;
    if(total < 0) total += MOD;
    lli inverseC = binPow(coeffs[k], MOD - 2);
    return total;
}



int main()
{
    //fastIO();
    lli n, k; cin>>n>>k;
    prec(k);
    

    cout << S(n, k)  << endl;
    

    return 0;
}