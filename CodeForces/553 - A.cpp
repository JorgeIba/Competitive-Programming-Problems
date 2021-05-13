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

const lli maxN = 1e6;
const lli MOD = 1e9+7;
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r)
{
    return (((fact[n]*invFact[n-r])%MOD)*invFact[r])%MOD;
}

int main () {
	//fastIO();
    prec();
    int n; cin>>n;
    vector<lli> balls(n);
    for(auto &x: balls) cin>>x;

    lli dp = 1, size = 0;
    for(int i = 0; i<n; i++)
    {
        dp =  dp*nCr(size + balls[i]-1, balls[i] - 1) % MOD;
        size += balls[i];
    }

    cout << dp << endl;
    
	return 0;
}