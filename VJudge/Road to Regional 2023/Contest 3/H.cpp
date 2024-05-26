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
	//fastIO();
	
    int n; cin>>n;
    string a, b; cin>>a>>b;

    auto get_idx = [&](const auto &get_idx, const string &x, int idx, lli l, lli r, bool rev) -> lli {
        // debugg(l);
        // debugg(r);
        // debugg(idx);
        // debugg(rev);
        // cout << endl;

        if(l == r) return l;

        lli mid = (l+r)/2;

        if(x[idx] == '0'){
            if(rev){
                return get_idx(get_idx, x, idx+1, mid+1, r, 1);
            } else {
                return get_idx(get_idx, x, idx+1, l, mid, 0);
            }
        } else{
            if(rev){
                return get_idx(get_idx, x, idx+1, l, mid, 0);
            } else {
                return get_idx(get_idx, x, idx+1, mid+1, r, 1);
            }
        }
    };

    lli r = (1LL << n);

    lli idx_a = get_idx(get_idx, a, 0, 0, r, false);
    lli idx_b = get_idx(get_idx, b, 0, 0, r, false);

    cout << idx_b - idx_a - 1 << endl;

	return 0;
}

