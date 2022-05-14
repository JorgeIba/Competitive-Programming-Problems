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


void solve(){
    lli a, b, c; cin>>a>>b>>c;

    if(c > a) swap(a, c);

    vector<lli> final_g(3);
    final_g[0] = a / 2;
    final_g[1] = a - (a/2);
    final_g[2] = c;

    // cerr << final_g[0] << " " << final_g[1] << " " << final_g[2] << endl;

    for(int i = 0; i < b; i++)
    {
        lli idx = (min_element(all(final_g)) - final_g.begin());
        final_g[idx]++;


        // cerr << final_g[0] << " " << final_g[1] << " " << final_g[2] << endl;
    }


    cout << *max_element(all(final_g)) << endl;

}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

