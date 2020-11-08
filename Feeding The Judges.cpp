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

const lli MOD = 188888881;

vector<lli> fact, inv, invfact;


void prec()
{
    int M = 2000000;
    fact.resize(M, 1);
    invfact.resize(M, 1);
    inv.resize(M, 1);
    for(lli i = 2; i < M; ++i){
		fact[i] = i * fact[i-1] % MOD;
		inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
		invfact[i] = (lli)inv[i] * invfact[i-1] % MOD;
	}
}


lli nCr(lli n, lli r)
{
    if(n<0) return 0;
    return ((fact[n] * invfact[r])%MOD * invfact[n-r])%MOD;
}


void solve(int n, vector<lli> rest)
{
    int k = SZ(rest);
    

    lli ans = 0;
    for(int i = 1; i<(1<<k); i++)
    {
        lli sum = 0;
        for(int j = 0; j<k; j++)
        {
            if(i & (1<<j) )
            {
                sum += (rest[j]+2);
            }
        }
        cerr << sum << endl;
        lli aux = nCr(n + k - 1 - sum, k-1);

        if(__builtin_popcount(i) & 1)
        {
            ans = (ans - aux)%MOD;
        }
        else
        {
            ans = (ans + aux)%MOD;
        }
    }
    cout << ans << endl;
}


int main () {
	//fastIO();
	prec();
    solve(2, {5, 5, 1});

    
	return 0;
}