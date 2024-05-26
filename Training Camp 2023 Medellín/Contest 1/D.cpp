#include <bits/stdc++.h>
 
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


void main_(){
    int n, m; cin>>n>>m;
    
    vector<lli> prices(n);
    for(auto &x: prices) cin>>x;

    // auto check = [&](lli money){
    //     int cnt = 0;
    //     forn(i, n){
    //         if(money >= prices[i]){
    //             cnt++;
    //             money -= prices[i];
    //         }
    //     }
    //     return cnt;
    // };

    // lli l = 0, r = 1e16, ans = -1;
    // bool impossible = true, rich = true;
    // while(l <= r){
    //     lli mid = (l+r)/2;
    //     int how_many = check(mid);
    //     cout << l << " --- " << r << " -- " << mid << " -> " << how_many << endl;
    //     if(how_many == m){
    //         impossible = false;

    //         ans = mid;
    //         l = mid+1;
    //     } else if(how_many > m){
    //         rich = false;
    //         r = mid-1;

    //     } else { // how_many < m
    //         l = mid+1;
    //     }
    // }

    vector< lli> valids;
    for(auto x: prices) {
        if(x == 0){
            m--;
        } else {
            valids.push_back(x);
        }
    }

    lli ans = 0;
    int i = 0;
    for(; i < m; i++){
        ans += valids[i];
    }

    bool impossible = (m < 0);
    bool rich = i == SZ(valids);

    // for(auto x: valids) cout << x << " ";
    // cout << endl;
    // cout << ans << " -- " << i << " .. " << SZ(valids) << endl;

    if(i < SZ(valids)) {
        int mini = *min_element(valids.begin() + i, valids.end());
        // cout << mini << endl;
        ans += mini-1;
    }
        
    
    if(impossible){
        cout << "Impossible" << endl;
    } else if(rich) {
        cout << "Richman" << endl;
    } else {
        assert(ans >= 0);
        cout << ans << endl;
    }
}


int main () {
	// fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

