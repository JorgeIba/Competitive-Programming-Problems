#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    vector<lli> coins = {1, 2, 5, 10, 20, 50,100};
    //vector<lli> coins = {2, 5, 3, 6};
    vector< vector<lli> > dp( (int) coins.size(), vector<lli>(201));

    for(int i = 0; i<coins.size(); i++)
    {
        dp[i][0] = 1;
    }

    for(int i = 0; i<coins.size(); i++)
    {
        lli coin = coins[i];
        for(int j = 1; j <= 200; j++)
        {
            dp[i][j] = ((i-1) >= 0?dp[i-1][j]:0) + ((j-coin) >= 0?dp[i][j-coin]:0);
        }
    }
    
    cout<<(dp[coins.size() - 1][200] + 1)<<endl;

    return 0;
}