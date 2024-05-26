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


const int MOD = 998244353;
const int MAXN = 2e5 + 1000;

lli fact[MAXN], invFact[MAXN];

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1; 
        a = a * a % MOD;
    }
    return res;
}

int main () {
	//fastIO();

    fact[0] = fact[1] = invFact[0] = invFact[1] = 1;
    forr(i, 2, MAXN-1) {
        fact[i] = 1LL * i * fact[i-1] % MOD;
        invFact[i] = powerMod(fact[i], MOD-2);
    }

    int n, k; cin>>n>>k;

    int curr = 0, ans = 0;
    for(int d = 0; d <= n; d++){
        int e = n - d;
        if(d > k) break;
        int ways_e = 1LL * fact[d+1] * powerMod(d+1, k-d) % MOD;
        ans += fact[n] * invFact[e] % MOD * (ways_e - curr + MOD) % MOD;
        if(ans >= MOD) ans -= MOD;

        curr = ways_e;
    }

    cout << ans << endl;


	return 0;
}

