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

const lli MOD = 1e9+7, maxN = 1e5;

vector<lli> fact, ifact;


lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = (res*a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}


void prec()
{
    fact.resize(maxN+1);
    ifact.resize(maxN+1);
    fact[0] = ifact[0] = 1;
    for(int i = 1; i<maxN; i++)
    {
        fact[i] = (fact[i-1]*i)%MOD;
        ifact[i] = binPow(fact[i], MOD-2, MOD);
    }
}

lli nChooseK(lli n, lli k)
{
    return (((fact[n] * ifact[n-k])%MOD)*ifact[k])%MOD;
}


int main () {
	//fastIO();
    prec();
    lli n, m; cin>>n>>m;
    if(m==0)
    {
        cout << fact[n] << endl;
        return 0;
    }
    cout << (nChooseK(n, 2) * fact[n-2*m])%MOD << endl;
    

	return 0;
}