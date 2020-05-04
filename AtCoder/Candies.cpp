#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

int main()
{
    fastIO();
    lli n, k;  cin>>n>>k;
    vector<lli> candies(n);
    vector<lli> prefix(100010);
    for(auto &x: candies)
    {
        cin>>x;
    }
    vector<vector<lli>> dp(n+1, vector<lli>(k+1, 0));

    
    for(int i = 0; i<=min(k, candies[0]); i++)
    {
        dp[0][i] = 1;
    }
    for(int i = 1; i<n; i++)
    {
        fill(all(prefix), 0);
        prefix[0] = dp[i-1][0];
        for(int l = 1; l<=k; l++ )
        {
            prefix[l] = prefix[l-1] + dp[i-1][l];
        }
        for(lli j = k ; j>=0; j--)
        {
            lli minimo = min(j, candies[i]);   
            dp[i][j] = (prefix[j] -  (j-minimo-1 >= 0? prefix[j-minimo-1]: 0))%MOD ;
        }
    }

    cout<<dp[n-1][k]<<endl;
    

    return 0;
}