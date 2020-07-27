#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
vector< vector< lli > > adj;
const lli INF = 1e15;
const lli MAXN = 1<<(11);
lli n; 
lli dp[MAXN][11];

void printAdj()
{
    for(int i = 0; i<=n; i++)
    {
        for(int j = 0; j<=n; j++)
            cout<<adj[i][j]<<" ";
        cout<<endl;
    }
}


lli fun(lli mask, lli idx)
{
    if(__builtin_popcount(mask) == n+1) return adj[idx][0];

    lli &res = dp[mask][idx];
    if( res != -1) return res;
    res = INF;

    for(lli i = 0; i<=n; i++)
    {
        if(! (mask & (1<<i)) )
        {
            res = min(res,  fun( (mask | (1<<i)) , i) + adj[idx][i]);
        }
    }
    return res;
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    cin>>n;
    adj.clear(); adj.assign( n+1, vector<lli> (n+1) );
    for(int i = 0; i<=n; i++)
    {
        for(int j = 0; j<=n; j++)
        {
            if(i != j) cin>>adj[i][j];
        }
    }

    cout<< fun(1, 0) << endl;
}

int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}