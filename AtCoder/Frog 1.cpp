#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli n; 
vector<lli> stones;

lli dp[100010];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin>>n;
    stones.resize(n);
    for(auto &x: stones)
    {
        cin>>x;
    }

    dp[0] = 0;
    dp[1] = abs(stones[0] -  stones[1]);
    for(int i = 2; i<n; i++)
    {
        dp[i] = min(  abs(stones[i] - stones[i-1]) + dp[i-1]  , abs(stones[i] - stones[i-2]) + dp[i-2]   );
    }

    cout<<dp[n-1]<<endl;

    return 0;
}