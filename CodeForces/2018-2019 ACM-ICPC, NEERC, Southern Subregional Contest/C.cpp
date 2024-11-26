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
	// fastIO();


    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    set<lli> odds;
    for(auto x: nums) {
        while(x % 2 == 0)
            x /= 2;
        odds.insert(x);
    }

    if(SZ(odds) > 1) {
        cout << -1 << endl;
        return 0;
    }

    lli ans = 0;
    multiset<lli> bacterias(all(nums));
    while(SZ(bacterias) > 1) {
        auto x_1 = *bacterias.begin(); bacterias.extract(x_1);
        auto x_2 = *bacterias.begin(); bacterias.extract(x_2);

        if(x_1 == x_2) {
            bacterias.insert(2*x_1);
        } else {
            ans++;
            bacterias.insert(2*x_1);
            bacterias.insert(x_2);
        }
    }

    cout << ans << endl;



	return 0;
}

