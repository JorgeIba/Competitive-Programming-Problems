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

const int MOD      = 1e9+1;
const int MAXN = 1e5 + 10;
const int MAXLEVEL = 17;
const int MAXMASK = 12;

vector< array<int,2> > fetch_nodes(int start) {
    
    vector<int> level(MAXN, -1);
    vector< array<int, 2> > nodes;

    queue<int> q;
    level[start] = 0;
    q.push(start);
    nodes.push_back({start, level[start]});

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        for(auto v: {2*u, 3*u}) {
            if(v > MAXN) continue;
            if(level[v] != -1) continue;
            level[v] = level[u]+1;
            q.push(v);
            nodes.push_back({v, level[v]});
        }
    }

    return nodes;
}

int main () {
	fastIO();

    auto nodes = fetch_nodes(1);
    // int max_level = 0, max_size = 0;

    // vector<int> level(15);
    // for(auto [x, lvl]: nodes) {
    //     max_level = max(max_level, lvl);
    //     level[lvl]++;
    // }

    // for(auto x: level) 
    //     max_size = max(max_size, x);


    // cout << max_level << " " << max_size << endl;

    auto calc_ans_for_n = [&](int n) {
        vector< vector<int> > level(MAXLEVEL);
        for(auto [x, lvl]: nodes) {
            if(x > n) continue;
            level[lvl].push_back(x);
        }

        vector< vector<int> > dp(MAXLEVEL, vector<int>(1 << MAXMASK, 0));
        dp[0][0] = 1;
        dp[0][1] = 1;

        for(int lvl = 0; lvl < MAXLEVEL-1; lvl++) {
            int sz = SZ(level[lvl]);
            for(int prev_mask = 0; prev_mask < (1 << sz); prev_mask++) {
                int sz_next = SZ(level[lvl+1]);
                int next_mask = (1 << sz_next) - 1;

                for(int j = 0; j < sz; j++) {
                    if(prev_mask & (1 << j)) {
                        if(j < sz_next) {
                            next_mask = next_mask & ~(1 << j);
                        }

                        if(j+1 < sz_next) {
                            next_mask = next_mask & ~(1 << (j+1));
                        }
                    }
                }

                for (int submask = next_mask; submask; submask = (submask - 1) & next_mask) {
                    (dp[lvl+1][submask] += dp[lvl][prev_mask]) %= MOD;
                }
                (dp[lvl+1][0] += dp[lvl][prev_mask]) %= MOD;
            }
        }

        int ans = 0;
        for(int i = 0; i < (1 << MAXMASK); i++) {
            for(int j = MAXLEVEL-1; j < MAXLEVEL; j++){
                (ans += dp[j][i]) %= MOD;
            }
        }
        return ans;
    };


    vector<int> dp(MAXN);
    dp[0] = 1;
    for(auto [n, _]: nodes) {
        dp[n] = calc_ans_for_n(n);
    }
    for(int i = 5; i < MAXN; i++){
        if(!dp[i])
            dp[i] = dp[i-1];
    }

    vector<int> roots;
    for(int i = 1; i < MAXN; i++) {
        if(i % 2 != 0 && i % 3 != 0){
            roots.push_back(i);
        }
    }

    int q; cin>>q;
    while(q--) {
        int n; cin>>n;
        int ans = 1;
        for(auto x: roots){
            if(x > n) break;
            ans = 1LL * ans * dp[n / x] % MOD;
        }
        cout << ans << endl;
    }

	return 0;
}

 