#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)
#define pb push_back

using namespace std;

typedef long long int lli;
typedef long double ld;

map<int, int> val_to_map;
vector<int> all_values;

struct WaveletTree {
    int lo, hi;
    unique_ptr<WaveletTree> left, right;
    unique_ptr<int[]> freq; 
    unique_ptr<lli[]> pref;

    WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) : lo(x), hi(y) {
        if (from >= to) return;
        int m = lo + (hi - lo) / 2;
        auto f = [m](int x) { return x <= m; };

        int size = distance(from, to) + 1;
        freq = make_unique<int[]>(size);
        pref = make_unique<lli[]>(size);

        int idx = 0;
        freq[idx] = 0;
        pref[idx++] = 0;

        for (auto it = from; it != to; ++it) {
            freq[idx] = freq[idx - 1] + f(*it);
            pref[idx] = pref[idx - 1] + all_values[*it];
            idx++;
        }

        if (hi != lo) {
            auto pivot = stable_partition(from, to, f);
            left = make_unique<WaveletTree>(from, pivot, lo, m);
            right = make_unique<WaveletTree>(pivot, to, m + 1, hi);
        }
    }

    int lessThanOrEqual(int l, int r, lli k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int lb = freq[l - 1], rb = freq[r];
        int leftCount = left ? left->lessThanOrEqual(lb + 1, rb, k) : 0;
        int rightCount = right ? right->lessThanOrEqual(l - lb, r - rb, k) : 0;
        return leftCount + rightCount;
    }

    lli sumLessThanOrEqual(int l, int r, lli k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return pref[r] - pref[l - 1];
        int lb = freq[l - 1], rb = freq[r];
        lli leftSum = left ? left->sumLessThanOrEqual(lb + 1, rb, k) : 0;
        lli rightSum = right ? right->sumLessThanOrEqual(l - lb, r - rb, k) : 0;
        return leftSum + rightSum;
    }
};
const int D = 50 + 5;

vector< lli > prefix_L[D];
vector< int > dims_L[D];
vector< int > dims_R[D];

lli get_ans_for_dim(int L, int R, int D, WaveletTree &WT_L, WaveletTree &WT_R){
    lli cnt_rs=0, cnt_ls=0;
    int ans = 0;

    int l = 0, r = SZ(all_values)-1;
    while(l <= r) {
        int mid = (l+r)/2;
        lli aux_cnt_rs = WT_R.lessThanOrEqual(L+1, R+1, mid);
        lli aux_cnt_ls = (R - L + 1) - WT_L.lessThanOrEqual(L+1, R+1, mid-1+1);
        if(aux_cnt_rs > aux_cnt_ls) {
            cnt_rs = aux_cnt_rs;
            cnt_ls = aux_cnt_ls;
            ans = mid;
            r = mid-1;
        } else {
            l = mid+1;
        }
    }

    int x = ans;
    lli sum_rs = WT_R.sumLessThanOrEqual(L+1, R+1, x);
    lli sum_ls = (prefix_L[D][R] - (L ? prefix_L[D][L-1] : 0)) - WT_L.sumLessThanOrEqual(L+1, R+1, x);

    lli left = cnt_rs * all_values[x] - sum_rs;
    lli right = sum_ls - cnt_ls * all_values[x];

    return left + right;
}


int main () {
	fastIO();

    auto map_number = [&](int x) {
        if(!val_to_map.count(x)) {
            int v = SZ(val_to_map);
            val_to_map[x] = v;
        }
        return val_to_map[x];
    };

    int n, d; cin>>n>>d;
    forn(i, d) {
        dims_L[i].resize(n);
        dims_R[i].resize(n);
        prefix_L[i].resize(n);
    }
    
    forn(i, n) {
        forn(j, d) {
            int l, r; cin>>l>>r;
            dims_L[j][i] = l;
            dims_R[j][i] = r;

            if(i)
                prefix_L[j][i] = prefix_L[j][i-1];
            prefix_L[j][i] += l;

            all_values.push_back(l);
            all_values.push_back(r);
        }
    }

    sort(all(all_values)); 
    all_values.erase(unique(all(all_values)), all_values.end());
    for(auto x: all_values) map_number(x);
    forn(i, n) {
        forn(j, d) {
            dims_L[j][i] = map_number(dims_L[j][i]);
            dims_R[j][i] = map_number(dims_R[j][i]);
        }
    }
    
    int q; cin>>q;
    vector< array<int,2> > queries(q);
    forn(test, q){
        int l, r; cin>>l>>r; l--, r--;
        queries[test] = {l, r};
    }
    vector< lli > ans(q);
    forn(dim, d) {
        WaveletTree WT_L(all(dims_L[dim]), *min_element(all(dims_L[dim])), *max_element(all(dims_L[dim])));
        dims_L[dim].clear();
        dims_L[dim].shrink_to_fit();


        WaveletTree WT_R(all(dims_R[dim]), *min_element(all(dims_R[dim])), *max_element(all(dims_R[dim])));
        dims_R[dim].clear();
        dims_R[dim].shrink_to_fit();

        forn(i, q) {
            auto [l, r] = queries[i];
            lli ans_dim = get_ans_for_dim(l, r, dim, WT_L, WT_R);
            ans[i] += ans_dim;
        }
    }

    for(auto x: ans) {
        cout << x << endl;
    }

	return 0;
}
