#include <bits/stdc++.h>
#define lli long long int

using namespace std;

const lli MAXN = 200010;


/*
lli funcion(lli index)
{
    if(index >= nums.size())
    {
        return 0;
    }
    if(dp[index] != -1)
    {
        return dp[index];
    }

    if(sig[index] != -1)
    {
        lli der = funcion(index+1) + 1;
        lli salto = funcion( sig[index]  ) + 1;
        return dp[index] = min(der,salto);
    }
    return dp[index]  = funcion(index + 1) + 1;

}
*/

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    vector<lli> sig(n,-1);
    vector<lli> aux(MAXN,-1);
    vector<lli> dp(n, 0);
    for(auto &x: nums)
    {
        cin>>x;
    }
    for(int i = 0; i<n; i++)
    {
        lli num = nums[i];
        if(sig[ num  ] != -1)
        {
            sig[ i ] = aux[ num ];
        }
        aux[num] = i;
    }

    for(int i = 1; i<n; i++)
    {
        if(sig[i] != -1)
        {
            dp[i] = min(dp[i-1], dp[sig[i]]) + 1;
        }
        else
        {
            dp[i] = dp[i-1] + 1;
        }
    }

    cout<<dp[n-1]<<endl;

}
int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}