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
    lli n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    map<lli,lli> available;
    for(auto x: nums) available[x]++;


    for(int i = n; i >= 1; i--){
        lli taken = -1;
        for(auto x: available){
            lli aux_x = x.first;
            assert(x.second > 0);
            while(aux_x){
                if(aux_x == i) {
                    taken = x.first;
                    break;
                }
                aux_x /= 2;
            }
            if(taken != -1) break;
        }

        if(taken != -1) {
            available[taken]--;
            if(!available[taken]) available.erase(taken);
        }
        else {
            cout << "NO" << endl;
            return;
        }


    }

    cout << "YES" << endl;

}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

