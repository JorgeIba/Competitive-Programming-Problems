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



const lli INF = 1e18;


int main () {
	fastIO();

    lli t; cin>>t;

    for(int i = 1; i<=t; i++)
    {
        lli n; cin>>n;
        vector<lli> nums(n);
        for(auto &x: nums) cin>>x;


        lli maxi = -INF;
        lli curr_maxi = 0;
    
        for (auto x: nums)
        {
            curr_maxi = curr_maxi + x;
            maxi = max(maxi, curr_maxi);

            curr_maxi = max(0LL, curr_maxi);
        }

        cout << "Case #" << i << ": " << maxi << endl;


    }

    

	return 0;
}

