#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector< vector<lli> > days;
    vector< vector<lli> > dp;
    days.assign(n, vector<lli>(3,0));
    dp.assign(n, vector<lli>(3,-1));

    for(auto &x: days)
    {
        cin>>x[0]>>x[1]>>x[2];
    }

    dp[n-1][0] = days[n-1][0];
    dp[n-1][1] = days[n-1][1];
    dp[n-1][2] = days[n-1][2];

    for(int i = n-2; i>=0; i--)
    {
        for(int j = 0; j<3; j++)
        {
            if(j==0)
            {
                dp[i][j] = max( days[i][j] + dp[i+1][1], days[i][j] + dp[i+1][2]  );
            }
            else if (j==1)
            {
                dp[i][j] = max(days[i][j] + dp[i+1][0], days[i][j] + dp[i+1][2]);
            }
            else
            {
                dp[i][j] = max(days[i][j] + dp[i+1][0], days[i][j] + dp[i+1][1] );
            }
        }
    }

    /*
    for(auto x: dp)
    {
        cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<endl;
    }
    */
    cout<<max( {dp[0][0], dp[0][1], dp[0][2] }  )<<endl;
    return 0;
}