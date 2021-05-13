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


const int maxN = 2e5+10;


void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<lli> fr(maxN,0);
    for(auto x: nums) fr[x]++;


    vector<lli> dp(maxN,0);

    lli ans = 0;
    for(lli i = maxN-1; i>=1; i--)
    {
        if(!fr[i]) continue;
        dp[i] = fr[i];
        for(lli j = 2; i*j<maxN; j++)
        {
            dp[i] = max(dp[i], fr[i] + dp[i*j]);
        }
    }
    for(auto x: nums) ans = max(ans, dp[x]);

    /*
    sort(all(nums));
    for(auto x: nums) cout << x << " " << dp[x] << endl;
    */

    cout << n - ans  << endl;
}


int main () {
	fastIO();
    
    lli t; cin>>t;

    while(t--) solve();

	return 0;
}