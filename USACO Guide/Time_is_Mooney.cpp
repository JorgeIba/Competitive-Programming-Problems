#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    ifstream cin("time.in");
    ofstream cout("time.out");

    lli n, m, c; cin>>n>>m>>c;
    vector< lli > money(n+1);
    for(int i = 1; i<=n; i++) cin>>money[i];
    vector< vector< lli > > adjList(n+1);
    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
    }
    const lli INF = 1e10;
    vector< vector< lli > > dp(1005, vector<lli>(1005, -INF)); //dp[t][u] -> best profit at city u in time t
    dp[0][1] = 0;
    //for(int t = 1; t<=1000; t++) dp[t][1] = -INF;
    for(int t = 0; t<1001; t++)
    {
        for(int u = 1; u<=n; u++)
        {   
            for(auto v: adjList[u])
            {
                dp[t+1][v] = max(dp[t+1][v], dp[t][u] + money[v]);
            }
        }
    }
    lli ans = -1;
    for(int t = 0; t<1001; t++)
    {
        ans = max(ans, dp[t][1] - c*t*t);
        //if((dp[t][1] - c*t*t)> 24) cout << t << " ";
    }
    cout << ans << endl;
    
    return 0;
}