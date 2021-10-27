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
    while(t--)
    {
        lli n; cin>>n;
        vector<lli> nums(n);
        for(auto &x: nums) cin>>x;
        lli mini = *(min_element(all(nums)));
        lli ans = 0;
        for(auto x: nums)
            if(x != mini)
                ans++;

        cout << ans << endl;
    }


	return 0;
}

