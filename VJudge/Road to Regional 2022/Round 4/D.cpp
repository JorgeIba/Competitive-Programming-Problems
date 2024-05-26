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

const lli MOD = 998244353;

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1; 
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

int main () {
	//fastIO();

    lli n; cin>>n;

    vector<vector<lli>> kids(n+1);

    for(int i = 1; i <= n; i++){
        lli m; cin>>m;
        for(int j = 0; j < m; j++) {
            lli k_j; cin>>k_j;
            kids[i].push_back(k_j);
        }
    }

    map<lli,lli> how_many_wants;
    for(int i = 1; i <= n; i++) {
        for(auto gift: kids[i]) {
            how_many_wants[gift]++;
        }
    }

    lli inv_n = powerMod(n, MOD-2, MOD);

    lli ans = 0;
    for(int i = 1; i <= n; i++) {
        lli prob_being_chosen = inv_n;
        lli inv_m = powerMod(SZ(kids[i]), MOD-2, MOD);
        for(auto gift: kids[i]) {
            lli prob_gift_chosen = inv_m;
            lli prob_choose_some_valid = how_many_wants[gift] * inv_n % MOD;

            lli prob_valid = prob_being_chosen * prob_gift_chosen % MOD * prob_choose_some_valid  % MOD;
            // cout << i << " " << gift << " " << prob_choose_some_valid << " " << prob_valid << endl;
            ans = (ans + prob_valid) % MOD;
        }
    }

    cout << ans << endl;


	return 0;
}

