#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MOD = 998244353;
const int MAXN = 1e3 + 100, MAXT = 1e4 + 100;


lli powerMod(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a %MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

lli dp[MAXT][2];

int main () {
	//fastIO();
	

    int n, x; cin>>n>>x;
    vector<int> times(n);
    for(auto &t: times) cin>>t;

    int inv_n = powerMod(n, MOD-2);

    memset(dp, -1, sizeof(dp));
    auto f = [&](const auto &f, int t, bool last_one) -> lli {
        if(t > x) {
            if(last_one) return 1;
            return 0;
        }

        lli &ans = dp[t][last_one];
        if(ans != -1) return ans;

        ans = 0;
        for(int i = 0; i < n; i++){
            lli ans_i = 1LL * inv_n * f(f, t + times[i], i == 0) % MOD;
            
            (ans += ans_i) %= MOD;
        }
        return ans;
    };

    cout << f(f, 0, 0) << endl;
    

    // Poly fr(x + 1);
    // for(auto &t: times) {
    //     if(t <= x) (fr[t] += (inv_n)) %= MOD;
    // }

    // const Poly I(1, 1);

    // auto dac = [&](const auto &dac, int l, int r) -> Poly {
    //     if(r < l){
    //         return I;
    //     }
    //     if(l == r) {
    //         if(fr[l]){
    //             Poly X(l+1);
    //             X[0] = 1;
    //             X[l] = fr[l];
    //             return powerP(X, x);
    //         } else return I;
    //     }
    //     int mid = (l+r)/2;
    //     auto R = dac(dac, l, mid) * dac(dac, mid+1, r); 
    //     R.resize(min(SZ(R), x+1));
    //     return R;
    // };

    // auto P = dac(dac, 0, x);

    // // P[0] = 1;
    // // P = powerP(P, x+1);
    // // P = P * P;
    // // // P = P * P;
    // // // P = P * P;
    // // // P = P * P;
    // // // P = P * P;
    // // // P = P * P;

    // forr(i, 0, SZ(P)-1) cout << P[i] << " ";
    // cout << endl;

    // lli ans = 0;
    // for(int i = 0; i <= x; i++){
    //     if(times[0] + i > x) {
    //         (ans += P[i]) %= MOD;
    //     }
    // }

    // cout << ans*inv_n % MOD << endl;




	return 0;
}

