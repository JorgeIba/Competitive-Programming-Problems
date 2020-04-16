#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n,k;  cin>>n>>k;
    vector<lli> dp;
    dp.resize(100010, INT_MAX);
    vector<lli> stones(n);    
    for(auto &x: stones)
    {
        cin>>x;
    }
    dp[0] = 0;
    dp[1] = abs(stones[1] - stones[0]);

    for(int i = 2; i < n; i++)
    {
        for(int j = 1; j<=k; j++)
        {
            if( i - j >= 0)
            {
                dp[i] = min(  abs(stones[i] - stones[i-j]) + dp[i-j] , dp[i] );
            }
        }
    }

    cout<<dp[n-1]<<endl;


    return 0;
}