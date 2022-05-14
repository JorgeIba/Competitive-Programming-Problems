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
    lli n, lemons_per, sugar_per; cin>>n>>lemons_per>>sugar_per;

    vector< array<lli,3> > days(n);
    for(int i = 0; i < n; i++) {
        cin>>days[i][0]>>days[i][1]>>days[i][2];
    }


    const lli INF = 1e9;
    lli min_lemon = INF, min_sugar = INF, ans = 0;
    lli sugar_left = 0;

    for(int i = 0; i < n; i++)
    {
        min_lemon = min(min_lemon, days[i][1]);
        min_sugar = min(min_sugar, days[i][2]);


        lli lemon_needed = days[i][0] * lemons_per;
        ans += lemon_needed * min_lemon;

        lli sugar_needed = days[i][0] * sugar_per;
        

        if(sugar_left >= sugar_needed) {
            sugar_left -= sugar_needed;
            ans += 0;
        } else {
            sugar_needed -= sugar_left;
            sugar_left = 0;
            lli bags = sugar_needed / 80;
            if(sugar_needed % 80) {
                bags++;
                sugar_left = 80 - (sugar_needed % 80);
            }
            ans += bags * min_sugar;
        }        
    }


    cout << ans << endl;
}



int main () {
	// fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

