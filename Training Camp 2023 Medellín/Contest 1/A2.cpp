#include <bits/stdc++.h> 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 

#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


struct Fenwick {
  vector<long long> tree;
  int n;

  void init(int _n) {
    n = _n;
    tree.resize(n+1, 0);
    for (int i = 0 ; i <= n ; i++) {
      tree[i] = 0;
    }
  }

  void update(int idx, long long val) {
    for (; idx <= n ; idx += idx & -idx) {
      tree[idx] += val;
    }
  }

  long long query(int idx) {
    long long ret = 0;
    while (idx > 0) {
      ret += tree[idx];
      idx -= idx & -idx;
    }
    return ret;
  }

  long long query(int x, int y) {
    return query(y) - query(x-1);
  }
};

const int MAXN = 1e5+10;
ordered_set<int> index[MAXN];
int colors[MAXN], vals[MAXN];


void main_(){
	int n, q; cin>>n>>q;


    forn(i, n)
        cin>>colors[i];

    forn(i, n)
        cin>>vals[i];

    forn(i, n)
        index[colors[i]].insert(i);

    Fenwick F; F.init(n);
    forn(i, n) F.update(i+1, vals[i]);


    auto get_cnt = [&](int l, int r, const vector<int> &colors){
        int cnt = 0;
        for(auto x: colors){
            cnt += index[x].order_of_key(r+1) - index[x].order_of_key(l);
        }
        return cnt;
    };

    auto get_l = [&](int fixed, const vector<int> &colors){
        int l = 0, r = fixed, ans = -1;
        while(l <= r){
            int mid = (l+r)/2;
            int cnt = get_cnt(mid, fixed, colors);
            int sizee = fixed - mid + 1;
            if(cnt == sizee) {
                ans = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        return ans;
    };

    auto get_r = [&](int fixed, const vector<int> &colors){
        int l = fixed, r = n-1, ans = -1;
        while(l <= r){
            int mid = (l+r)/2;
            int cnt = get_cnt(fixed, mid, colors);
            int sizee = mid - fixed + 1;
            if(cnt == sizee) {
                ans = mid;
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        return ans;
    };


    while(q--){
        int t; cin>>t;
        if(t == 1){
            int p, x; cin>>p>>x; p--;
            auto itr = index[ colors[p] ].find(p);
            assert(itr != index[ colors[p] ].end());

            index[ colors[p] ].erase(itr);
            index[ x ].insert(p);

            colors[p] = x;

            // ST.update(p, x); 
        } else if(t == 2){
            int p, x; cin>>p>>x;
            int pos_x = F.query(p, p);
            F.update(p, x - pos_x);
            // F.update(p, x);
        } else {
            int x, k; cin>>x>>k; x--;
            vector<int> col(k);
            for(auto &xx: col) cin>>xx;
            int l = get_l(x, col);
            int r = get_r(x, col);

            cout << F.query(l+1, r+1) << endl;
        }
    }


    forr(i, 1, n) index[i].clear();
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

