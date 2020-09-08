#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector<lli> > adj;
vector< lli > dp(100010, 0);


lli dfs(lli index)
{
    if(dp[index]!= 0)  return dp[index];
    for(auto v: adj[index])
    {
        dp[index] = max(dp[index], 1 + dfs(v) );
    }
    return dp[index];
}

int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    adj.resize(n);
    forn(i, 0, m)
    {
        lli x, y; cin>>x>>y;
        x--,y--;
        adj[x].push_back(y);
    }

    for(int i = 0; i<n; i++)
    {
        dfs(i);
    }
    lli res = 0;
    forn(i, 0, n)
        res = max(res, dp[i]);
        //cout<<dp[i]<<" ";
    cout<<res<<endl;
    return 0;
}
