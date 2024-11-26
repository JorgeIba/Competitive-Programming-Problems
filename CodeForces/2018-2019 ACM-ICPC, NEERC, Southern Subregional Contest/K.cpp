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
typedef vector<int> vi;

struct WavTree {
    int low, high;
    WavTree *left, *right;
    vi mapLeft;

    WavTree(vi::iterator from, vi::iterator to, int x, int y): low(x), high(y) {
        if(from >= to) return;
    
        int m = (low + high) / 2;
        auto f = [m](int x) { return x <= m; };
        mapLeft.reserve(to - from + 1);
        mapLeft.push_back(0);
        for(auto it = from; it != to; it++) {
            auto leq = f(*it);
            mapLeft.push_back(mapLeft.back() + leq);
        }
        if(high != low) {
            auto pivot = stable_partition(from, to, f);
            left = new WavTree(from, pivot, low, m);
            right = new WavTree(pivot, to, m+1, high);
        }
    }

    int kth(int l, int r, int k) {
        if(l > r) return -1;
        if(low == high)
            return low;
        int lb = mapLeft[l-1], rb = mapLeft[r];
        int inLeft = rb - lb;
        if(k <= inLeft)
            return left->kth(lb+1, rb, k);
        else 
            return right->kth(l - lb, r - rb, k - inLeft);
    }
};

const int INF = 1e9;

int main () {
	// fastIO();

    int n, m; cin>>n>>m;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    auto to_wt = nums;
    WavTree WT(all(to_wt), *min_element(all(to_wt)), *max_element(all(to_wt)));

    vector< vector<bool> > is_valid(n, vector<bool>(n));

    for(int l = 0; l < n; l++) {
        for(int r = l; r < n; r++) {
            int sz = (r - l + 1);
            int k = (sz+1) / 2;
            auto med = WT.kth(l+1, r+1, k);
            
            // cout << l << " -- " << r << " ---> " << med << " ---> " << k << endl;
            
            if(med >= m) {
                is_valid[l][r] = true;
            }
        }
    }


    vector< int > dp(n, -1);

    auto f = [&](const auto &f, int l) {
        if(l >= n) return 0;

        auto &ans = dp[l];
        if(ans != -1) return ans;

        ans = -INF;
        for(int r = l; r < n; r++) {
            if(is_valid[l][r]) {
                ans = max(ans, f(f, r+1) + 1);
            }
        }
        
        return ans;
    }; 

    auto ans = f(f, 0);
    // debugg(ans);
    cout << (ans >= 0 ? ans : 0) << endl;
    




	return 0;
}

