#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const lli MAXN = 100 + 100;
const lli MOD = 1e9+7; 
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec()
{
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


lli dp[MAXN][MAXN][MAXN];

lli f(int idx, int spaces, const int k) {
    if(idx == 0) return spaces == 0;
    if(spaces < 0) return 0;

    lli &ans = dp[idx][spaces][k];
    if(ans != -1) return ans;

    ans = 0;

    for(int j = 0; j <= k-1; j++) {
        lli ways = nCr(spaces, j);
        ans += ways * f(idx-1, spaces - j, k) % MOD;
        if(ans >= MOD) ans -= MOD;
    }

    return ans;
}


int main () {
	// fastIO();
    prec();

    memset(dp, -1, sizeof(dp));
    lli n, k; 

    while(cin>>n>>k) {
        if(n == 1) cout << 1 << endl;
        else cout << f(n, n-2, k) << endl;
    }
	return 0;
}

