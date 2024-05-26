#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

int lsb(lli n){
    lli idx_lsb= 0;
    while(!((1LL << idx_lsb) & n)) idx_lsb++;
    return idx_lsb;
}


void solve() {
    lli a, b, d; cin>>a>>b>>d;

    lli c = a | b;
    
    lli lsb_d = lsb(d), lsb_c = lsb(c);

    if(lsb_d > lsb_c) {
        cout << -1 << endl;
        return;
    }

    lli ans = 0;
    for(int i = 0; i < 30; i++) {
        if(((1ll << i) & c) && !((1LL << i) & ans)) {
            lli dist = i - lsb_d;
            ans += d*(1LL<<dist);
        }
    }

    assert( (a|ans) % d == 0 && (b|ans) % d == 0);

    cout << ans << endl;
}



int main () {
	// fastIO();

    int t; cin>>t;

    while(t--) solve();

	return 0;
}

