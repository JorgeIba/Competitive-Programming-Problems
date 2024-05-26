#include <bits/stdc++.h>

#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void solve(){
    lli n; cin>>n;

    vector<lli> nums(n/2);
    for(auto &x: nums) {
        cin>>x;
    }

    if( SZ(set<lli>(all(nums))) !=  n/2 ) {
        cout << -1 << endl;
        return;
    }

    set<lli> available;
    for(int i = 1; i <= n; i++) available.insert(i);
    for(auto x: nums) available.erase(x);

    vector<lli> ans(n);
    for(int i = n/2 - 1; i >= 0; i--) {
        auto num = nums[i];
        auto itr = prev(available.lower_bound(num));

        // cout << num << " " << *itr << " " << endl;

        if(itr == available.end() || num < *itr) {
            cout << -1 << endl;
            return;
        }

        ans[2*i] = *itr;
        ans[2*i+1] = num;

        available.erase(*itr);
    }

    for(auto a: ans) cout << a << " ";
    cout << endl;
}


int main () {
	fastIO();

    int t; cin>>t;
    while(t--) solve();

	return 0;
}

