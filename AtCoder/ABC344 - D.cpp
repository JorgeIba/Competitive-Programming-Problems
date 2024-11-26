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


int main () {
	// fastIO();

    string t; cin>>t;

    int n; cin>>n;
    vector< vector<string> > ss(n);
    forn(i, n) {
        int k; cin>>k;
        ss[i].resize(k);
        for(auto &s: ss[i]) {
            cin>>s;
        }
    }


    const int INF = 1e9;
    int m = SZ(t);

    vector< vector<int> > dp(m+1, vector<int>(n+1, -1));


    auto f = [&](auto const f, int idx_t, int idx_bag) {
        if(idx_t == m) return 0;
        if(idx_bag == n) return INF;

        int &ans = dp[idx_t][idx_bag];
        if(ans != -1) return ans;

        ans = f(f, idx_t, idx_bag+1);
        for(auto s: ss[idx_bag]) {
            if(SZ(s) > m - idx_t + 1) continue;

            bool check = true;
            for(int i = 0, j = idx_t; i < SZ(s); i++, j++) {
                if(s[i] != t[j]) check = false;
            }

            // cout << idx_t << " " << idx_bag << " --- " << SZ(s) << " == " << check << endl;
            if(check) {
                ans = min(ans, f(f, idx_t + SZ(s), idx_bag+1) + 1);
            }
        }

        return ans;
    };
    
    auto ans = f(f, 0, 0);

    // cout << ans << endl;
    cout << (ans == INF ? -1 : ans) << endl;


	return 0;
}

