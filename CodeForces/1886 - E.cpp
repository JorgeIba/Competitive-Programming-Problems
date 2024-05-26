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


const int INF = 1e9;


int main () {
	// fastIO();

    int n, m; cin>>n>>m;

    vector< array<int,2> > a(n);
    vector<int> b(m);
    forn(i, n){
        cin>>a[i][0];
        a[i][1] = i;
    }
    for(auto &x: b) cin>>x;

    sort(all(a)); reverse(all(a));

    vector<vector<int>> next(m, vector<int>(n+10, n+10));

    auto check = [&](int &mn, int l, int r, int i) {
        mn = min(mn, a[r][0]);
        return 1LL * mn * (r - l + 1) < b[i];
    };

    for(int i = 0; i < m; i++) {
        for(int l = 0, r = 0; l < n; l++) {     
            int mn = a[l][0];
            r = max(r, l);
            while(r < n && check(mn, l, r, i)) {
                // cout << l << " --- " << r << endl;
                // assert(l <= r);
                r++;
            }
            assert(l <= r);
            next[i][l] = (r < n ? r : INF);
        }
    }


    // for(int i = 0; i < m; i++) {
    //     cout << b[i] << " --- " << endl;
    //     for(int l = 0; l < n; l++) {
    //         cout << next[i][l] << " ";
    //     }
    //     cout << endl;
    // }
    // return 0;


    vector< int > dp(1 << m, n + 10);
    vector< int > comes_from(1 << m);

    dp[0] = -1;
    for(int mask = 0; mask < (1 << m); mask++) {
        for(int j = 0; j < m; j++) {
            int next_mask = mask ^ (1 << j);
            if(~mask & (1 << j)) {
                if(dp[mask]+1 > n+5) continue;
                int nxt = next[j][dp[mask] + 1];
                if(nxt < dp[next_mask]) {
                    comes_from[next_mask] = j;
                    dp[next_mask] = nxt;
                }
            }
        }
    }

    int least = dp[(1 << m) - 1];
    if(least >= n) {
        cout << "NO" << endl;
        return 0;
    } 

    cout << "YES" << endl;
    int curr_mask = (1 << m) - 1;
    vector< vector<int> > ans(m);
    while(curr_mask) {
        // for(int j = 0; j < m; j++) {
            int j = comes_from[curr_mask];
            assert(curr_mask & (1 << j));
            if(curr_mask & (1 << j)) {
                int prev_mask = curr_mask ^ (1 << j);
                if(dp[curr_mask] == next[j][dp[prev_mask] + 1]){
                    for(int l = dp[prev_mask]+1; l <= dp[curr_mask]; l++) {
                        ans[j].push_back( a[l][1] );
                    }

                    curr_mask = prev_mask;
                }
            }
        // }
    }

    forn(i, m) {
        cout << SZ(ans[i]) << " ";
        for(auto x: ans[i]) cout << x+1 << " ";
        cout << endl;
    }




	return 0;
}

