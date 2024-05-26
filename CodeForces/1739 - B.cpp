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


int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) {
        lli n; cin>>n;
        vector<lli> nums(n);
        for(auto &x: nums) cin>>x;

        vector<lli> sol(n);
        sol[0] = nums[0];


        bool unique_ans = true;
        for(int i = 1; i < n; i++) {
            lli sol1 = nums[i] + sol[i-1];
            lli sol2 = sol[i-1] - nums[i];
            if(sol1 >= 0 && sol2 >= 0 && sol1 != sol2) {
                unique_ans = false;
            }
            sol[i] = sol1;
        }

        if(!unique_ans) {
            cout << -1 << endl;
        } else {
            for(auto x: sol) cout << x << " ";
            cout << endl;
        }


    }


	return 0;
}

