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
    lli n, k; cin>>n>>k;

    string s; cin>>s;

    vector<lli> nums(26);
    for(auto x: s){
        nums[x-'a']++;
    }

    


    lli pairs = 0, odds = 0;
    for(auto x: nums){
        if(x % 2 == 1){
            odds++;
            x--;
        }
        while(x)
        {
            pairs++;
            x -= 2;
        }
    }


    lli vueltas = pairs/k;
    lli pairs_to_use = vueltas*k;

    lli ans = 2*vueltas;

    // cout << pairs << " " << pairs_to_use << " " << odds << endl;

    lli remains = odds + 2*(pairs - pairs_to_use);
    if(remains >= k) ans++;

    cout << ans << endl;
}




int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

