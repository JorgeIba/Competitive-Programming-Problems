#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


const int LOG = 24;

int to_mask(const string &s) {
    int mask = 0;
    for(auto c: s)
        mask |= (1 << (c - 'a'));
    return mask;
}

int main () {
	//fastIO();

    int n; cin>>n;
    vector< string > dict(n);
    for(auto &s: dict) cin>>s;


    vector<int> dp(1 << LOG);
    for(auto s: dict) 
        dp[to_mask(s)]++;


    for(int i = 0; i < LOG; i++){
        for(int mask = (1 << LOG) - 1; mask >= 0; mask--){
            if(mask & (1 << i)) 
                dp[mask ^ (1 << i)] += dp[mask];
        }
    }

    vector<int> dp_ans(1 << LOG);
    auto get_sgn = [](int mask){
        return __builtin_popcountll(mask) & 1 ? +1 : -1;
    };

    for(int mask = 0; mask < (1 << LOG); mask++){
        dp_ans[mask] = get_sgn(mask) * dp[mask];
    }

    for(int i = 0; i < LOG; i++) {
        for(int mask = 1; mask < (1 << LOG); mask++){
            if(~mask & (1 << i)) {
                dp_ans[mask ^ ( 1 << i)] += dp_ans[mask];
            }
        }
    }

    int ans = 0;
    for(int mask = 1; mask < (1 << LOG); mask++){
        ans ^= dp_ans[mask] * dp_ans[mask];
    }
    cout << ans << endl;

	return 0;
}
