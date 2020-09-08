#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> nums;
vector<lli> dp;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, m; cin>>n>>m;
    nums.resize(n);
    dp.resize(n+m, 0);
    

    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
    }
    for(int i = m; i<n; i++)
    {
        //cout<<(i+m)<<"\n";
        dp[i+m] = max(nums[i] + dp[i], dp[i+m-1] ) ; 
    }

    cout<<dp[n+m-1]<<endl;


    return 0;
}