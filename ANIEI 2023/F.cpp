#pragma GCC optimize("O3")
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

const int MAXK = 1e9 + 100;
const int MAX = 2e7 + 5e6;

namespace seg {
	lli seg[MAX], lazy[MAX];
    int R[MAX], L[MAX], ptr;
	int get_l(int i){
		if (L[i] == 0) L[i] = ptr++;
		return L[i];
	}
	int get_r(int i){    
		if (R[i] == 0) R[i] = ptr++;
		return R[i];
	}

	void build() { ptr = 2; }

	void prop(int p, int l, int r) {
		if (!lazy[p]) return;
		seg[p] += lazy[p] * (r-l+1);
		if (l != r) lazy[get_l(p)] += lazy[p], lazy[get_r(p)] += lazy[p];
		lazy[p] = 0;
	}

	lli query(int a, int b, int p=1, int l=0, int r=MAXK-1) {
		prop(p, l, r);
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];

		int m = l + (r-l)/2;
		return query(a, b, get_l(p), l, m)+query(a, b, get_r(p), m+1, r);
	}

	lli update(int a, int b, int val, int p=1, int l=0, int r=MAXK-1) {
		prop(p, l, r);
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			lazy[p] += val;
			prop(p, l, r);
			return seg[p];
		}
		int m = l + (r-l)/2;
		return seg[p] = update(a, b, val, get_l(p), l, m)+update(a, b, val, get_r(p), m+1, r);
	}
};


int main () {
	fastIO();
	
    int n, k; cin>>n>>k;

    seg::build();

    vector< int > endpoints;
    forn(i, n){
        int l, r, x; cin>>l>>r>>x;
        seg::update(l, r, x);
        endpoints.push_back(l);
        endpoints.push_back(r);
    }

    sort(all(endpoints));
    endpoints.erase(unique(all(endpoints)), endpoints.end());

    lli ans = 0;
    for(auto idx: endpoints) {
        int l = max(1, idx - k + 1);
        int r = min(idx + k - 1, MAXK - 5);
        
        ans = max(ans, seg::query(l, idx));
        ans = max(ans, seg::query(idx, r));
    }
    cout << ans << endl;

	return 0;
}

