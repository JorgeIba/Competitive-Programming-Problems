#include <bits/stdc++.h>
#define lli long long int

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector< vector<lli> > nums;
    vector< vector<lli> > dp;
    nums.assign(2, vector<lli>(n,0) );
    dp.assign(3, vector<lli>(n,0) );
    for(auto &x: nums[0])
    {
        cin>>x;
    }
    for(auto &x: nums[1])
    {
        cin>>x;
    }
    dp[0][n-1] = nums[0][n-1];
    dp[1][n-1] = nums[1][n-1];
    dp[2][n-1] = 0;

    for(int i = n-2; i>=0; i--)
    {
        for(int j = 0; j<3; j++)
        {
            if(j==0) dp[0][i] = max(  dp[1][i+1], dp[2][i+1]  ) + nums[0][i];
            if(j==1) dp[1][i] = max(  dp[0][i+1], dp[2][i+1]  ) + nums[1][i];
            if(j==2) dp[2][i] = max(  dp[0][i+1], dp[1][i+1]  );
        }
    }

    /*
    for(auto x: dp)
    {
        for(auto y: x)
        {
            cout<<y<<" ";
        }
        cout<<endl;
    }
    */

    cout<<(max( {dp[0][0], dp[2][0], dp[1][0]}   ))<<endl;
    
    



    return 0;
}