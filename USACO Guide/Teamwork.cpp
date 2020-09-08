#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    //fastIO();
    ifstream cin("teamwork.in");
    ofstream cout("teamwork.out");
    lli n, K; cin>>n>>K;
    vector< lli > nums(n+1);
    for(int i = 1; i<=n; i++) cin>>nums[i];

    vector< lli > dp(n+1);
    dp[0] = 0;
    dp[1] = nums[1];
    for(int i = 1; i<=n; i++)
    {
        lli maximum = nums[i];
        for(int k = 1; k<=K; k++)
        {
            if(i-k+1 < 0 || (i-k) < 0) continue;
            maximum = max(maximum, nums[i-k+1]);
            dp[i] = max(dp[i], dp[i-k] + maximum*(k));
        }
    }
    //for(int i = 1; i<=n; i++) cout << dp[i] << " ";
    cout << dp[n] << endl;

    
    return 0;
}