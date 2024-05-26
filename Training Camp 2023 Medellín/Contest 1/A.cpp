#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
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

typedef cc_hash_table<int, int, hash<int>> umapp;

const int MAXN = 1e5+1;
const int MAXK = 1e5+1;
int colors_test[MAXK];
int colors[MAXN];
int vals[MAXN];
lli treee[MAXN];
int n;
umapp treem[MAXN];

struct Fenwick {
  int n;

  void init(int _n) {
    n = _n;
    forn(i, n+1) treem[i].clear();    
  }

  void update(int idx, int val, int frq) {
    idx++;
    for (; idx <= n ; idx += idx & -idx) {
        treem[idx][val] += frq;
        if(treem[idx][val] == 0) treem[idx].erase(val);
    }
  }

  int query(int idx, int k) {
    int ret = 0;
    while (idx > 0) {
        forn(i, k){
            auto itr = treem[idx].find(colors_test[i]);
            if(itr != treem[idx].end())
                ret += itr->second;
        }
        idx -= idx & -idx;
    }
    return ret;
  }

  int query(int x, int y, int k) {
    return query(y+1, k) - query(x-1+1, k);
  }
};



void init(int _n) {
    n = _n;
    for (int i = 0 ; i <= n ; i++) {
        treee[i] = 0;
    }
}

void update(int idx, int val) {
    for (; idx <= n ; idx += idx & -idx) {
        treee[idx] += val;
    }
}

long long query(int idx) {
    long long ret = 0;
    while (idx > 0) {
        ret += treee[idx];
        idx -= idx & -idx;
    }
    return ret;
}

long long query(int x, int y) {
    return query(y) - query(x-1);
}


void main_(){
	int n, q; cin>>n>>q;

    forn(i, n)
        cin>>colors[i];

    forn(i, n)
        cin>>vals[i];
    

    Fenwick ST; ST.init(n);
    forn(i, n){
        ST.update(i, colors[i], 1);
    }

    init(n);
    forn(i, n) update(i+1, vals[i]);

    int k;

    auto get_l = [&](int fixed){
        int l = 0, r = fixed-1, ans = fixed;
        while(l <= r){
            int mid = (l+r)>>1;
            int cnt = ST.query(mid, fixed, k);
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

    auto get_r = [&](int fixed){
        int l = fixed+1, r = n-1, ans = fixed;
        while(l <= r){
            int mid = (l+r)>>1;
            int cnt = ST.query(fixed, mid, k);
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
            
            if(colors[p] == x) continue;

            ST.update(p, colors[p], -1);
            ST.update(p, x, 1);
            colors[p] = x;
        } else if(t == 2){
            int p, x; cin>>p>>x;

            if(x == vals[p-1]) continue;

            update(p, x - vals[p-1]);
            vals[p-1] = x;
        } else {
            int x; cin>>x>>k; x--;
            forn(i, k){
                cin>>colors_test[i];
            }
            
            int l = get_l(x);
            int r = get_r(x);
            
            auto anss = query(l+1, r+1);
            
            cout << anss << endl;
        }
    }

}

int main () {
	fastIO();
	
	int t = 1;
	cin>>t;

    
	while(t--) main_();


	return 0;
}

