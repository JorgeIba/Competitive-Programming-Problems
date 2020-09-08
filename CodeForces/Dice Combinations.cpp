#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 1e6+10, MOD = 1e9 + 7;
lli dp[maxN];
/*
lli fun(lli sum)
{
    if(sum == 0) return 1;
    if(sum < 0 ) return 0;

    if(dp[sum] != -1) return dp[sum];
    lli res = 0;
    for(int i = 1; i<=6; i++)
    {
        res += fun(sum-i) % MOD;
    }
    return dp[sum] = res%MOD;
}
*/

int main()
{
    //fastIO();
    //memset(dp, -1, sizeof(dp));
    lli n; cin>>n;
    //cout << fun(n) << endl;
    dp[0] = 1;
    for(int i = 0; i<=n; i++)
    {
        for(int j = 1; j<=6; j++)
        {
            dp[i+j] += dp[i] % MOD;
        }
    }
    cout<<dp[n] % MOD <<endl;

    return 0;
}