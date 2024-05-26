#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

const lli MOD = 1e9+7;
const lli LOG = 21;


int main () {
	//fastIO();

    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<lli> dp(1 << LOG);

    for(auto x: nums) dp[x]++;

    for(int i = 0; i < LOG; i++) {
        for(int mask = (1 << LOG) - 1; mask >= 0; mask--){
            if(mask & (1 << i))
                dp[mask ^ (1 << i) ] += dp[mask];
        }
    }

    lli ans = 0;
    for(int mask = 0; mask < (1 << LOG); mask++){
        int bits = __builtin_popcountll(mask);

        if(bits & 1){
            ans = (ans - (powerMod(2, dp[mask], MOD) - 1) + MOD) % MOD;
        }else {
            ans = (ans + (powerMod(2, dp[mask], MOD) - 1 + MOD) % MOD) % MOD;
        }
    }
 
    cout << ans << endl;


	return 0;
}

