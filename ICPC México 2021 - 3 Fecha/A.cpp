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

lli n, R;

const int MAXN = 5000 + 100;
const lli MOD = 1e9+7;

lli lowers[MAXN], inverse[MAXN];

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


lli dp[MAXN][2];


lli f(lli idx, int how_many){
    if(idx > n){
        if(how_many) return MOD-1;
        return 1;
    }

    lli &ans = dp[idx][how_many];
    if(ans != -1) return ans;

    ans = 0;

    lli N = R - lowers[idx] + 1, comb = N;
    for(int k = 1; k <= n - idx + 1; k++) {

        if(k > N) break;

        int new_how_many = (how_many + k - 1);
        assert(new_how_many >= 0);

        ans += comb * f(idx+k, new_how_many & 1) % MOD;
        if(ans >= MOD) ans -= MOD;

        comb = comb * (N - k) % MOD * inverse[k+1] % MOD;
    }


    return ans;
}

int main () {
	fastIO();
    cin>>n>>R;
    
    forr(i, 1, n+10) {
        inverse[i] = powerMod(i, MOD-2, MOD);
    }

    forr(i, 1, n) {
        cin>>lowers[i];
    }

    for(int i = n-1; i >= 1; i--) {
        lowers[i] = max(lowers[i], lowers[i+1]);
    }

    memset(dp, -1, sizeof(dp));
    cout << f(1, 0) << endl;

	return 0;
}

