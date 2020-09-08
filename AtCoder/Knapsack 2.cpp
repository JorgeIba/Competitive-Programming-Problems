#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli dp[110][100010];
const lli INF = 1e18;

int main()
{
    //fastIO();
    lli n, W; cin>>n>>W;
    vector< pair<lli,lli> > nums(n);
    for(auto &x: nums) cin>>x.first>>x.second;

    forn(i,0,105) forn(j,0,100005) dp[i][j] = INF;

    forn(i,0,n+1) dp[i][0] = 0;
    for(int i = 0; i<n; i++)
    {
        pair<lli,lli> bolsa = nums[i];
        for(int v = 0; v<=100005; v++)
        {
            dp[i+1][v] = min(dp[i][v], dp[i+1][v]);
            dp[i+1][v+bolsa.second] = min(dp[i][v] + bolsa.first, dp[i+1][v+bolsa.second]);   
        }
    }

    // El mejor de todos los dp[n][i]
    lli ans = 0;

    for(int i = 0; i<=100001; i++)
    {
        if(dp[n][i] <= W)
        {
            ans = i;
        }
    }
    
    cout << ans << endl;

    return 0;
}