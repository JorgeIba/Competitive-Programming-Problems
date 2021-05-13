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

const int MOD = 1e9+7;
const int maxN = 1e7;
vector<lli> fact(maxN+1), invFact(maxN+1);

lli binPow(lli a, lli b)
{
    lli res = 1; 
    while(b)
    {
        if(b&1) res = res*a % MOD;
        b >>= 1;
        a = a*a%MOD;
    }
    return res;
}


void prec()
{
    fact[0] = invFact[0] = 1;
    for(lli i = 1; i<maxN; i++)
    {
        fact[i] = i * fact[i-1] % MOD;
        invFact[i] = binPow(fact[i], MOD-2); //Las operaciones deben ir mod MOD
    }
}

lli nCk(lli n, lli k)
{
    return fact[n] * invFact[n-k] % MOD * invFact[k] % MOD; //Overflow
}

int main () {
	//fastIO();
    prec();
    for(lli n = 2; n<=13; n++)
    {
        
        lli ans = 0;
        for(lli i = 1; i<=n; i++)
        {
            lli aux = nCk(n, i) * fact[(n-i)] % MOD;
            if(i % 2 == 1) ans += aux;
            else ans -= aux;
        }

        cout << fact[n] - ans << " " << fact[n] / exp(1) << endl;
    }
    

	return 0;
}