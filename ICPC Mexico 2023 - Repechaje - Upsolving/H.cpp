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

struct SegmentTree {
    int n;
    lli neutro;
    vector<lli> ST;

    SegmentTree(int n, lli neutro): n(n), neutro(neutro), ST(2*n, neutro) {}

    void update(int idx, lli val) {
        idx += n;
        ST[idx] = max(ST[idx], val);
        for(; idx > 1; idx >>= 1) {
            ST[idx >> 1] = max(ST[idx], ST[idx ^ 1]);
        }
    }

    lli query(int l, int r) {
        lli val = neutro;
        for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) 
                val = max(val, ST[l++]);
            if(~r & 1) 
                val = max(val, ST[r--]);
        }
        return val;
    }
};

int main () {
    // fastIO();

    int n, S; cin>>n>>S;

    vector<lli> all_p;
    vector< array<lli,3 > > ranges(n);
    for(auto &[l, r, c]: ranges) {
        cin>>l>>r>>c;
        all_p.push_back(l);
        all_p.push_back(r);
    }

    sort(all(all_p));
    all_p.erase(unique(all(all_p)), all_p.end());
    all_p.push_back(2e9);

    int m = SZ(all_p);

    auto get_next = [&](int x) {
        return upper_bound(all(all_p), x) - begin(all_p);
    };

    auto get_idx = [&](int x) {
        return lower_bound(all(all_p), x) - begin(all_p);
    };

    sort(all(ranges));
    SegmentTree ST(m, 0);
    SegmentTree ST2(m, 0);
    vector<lli> dp(m);

    lli best_dp = 0;
    for(int i = n-1; i >= 0; i--) {
        auto [l, r, c] = ranges[i];
        int idx_l = get_idx(l);
        int idx_r = get_idx(r);

        int next_l = get_next(l);
        int next_r = get_next(r);
    
        lli dp_dont_take = best_dp;
        lli dp_take_all = 1LL * (r - l + 1) * S - c + ST2.query(next_r, m-1);
        lli dp_best_inside = ST.query(next_l, idx_r) - l * S - c;


        dp[idx_l] = max({dp[idx_l], dp_dont_take, dp_take_all, dp_best_inside});

        ST.update(idx_l, l * S + dp[idx_l]);
        ST2.update(idx_l, dp[idx_l]);

        best_dp = max(best_dp, dp[idx_l]);
    }

    cout << dp[0] << endl;

	return 0;
}
