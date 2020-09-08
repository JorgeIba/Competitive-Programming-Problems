#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = 1e18;

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    vector<lli> dp(n+1, -INF);
    dp[0] = 0;
    for(int i = 1; i<=n; i++)
    {
        for(int j = 1; j<=i; j++)
        {
            dp[i] = max(dp[i], nums[j-1] + dp[i-j]);
        }
    }
    cout<<dp[n]<<endl;


}



int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}