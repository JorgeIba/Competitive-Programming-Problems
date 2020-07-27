#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxM = 1e3 + 10, maxN = 15 + 1;

struct attempt
{
    lli u, v;
    ld p;
};

ld dp[maxM][1<<maxN];

int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    vector<attempt> tries(m);
    forn(i,0,m)
    {
        cin>>tries[i].u >> tries[i].v >> tries[i].p;
        tries[i].u--;
        tries[i].v--;
    }
    
    dp[0][(1<<n)-1] = 1;

    for(int i = 0; i<m; i++)
    {
        for(int mask = 0; mask<(1<<n); mask++)
        {
            lli u = tries[i].u, v = tries[i].v;
            ld p = tries[i].p;
            if( ! (mask&(1<<u)) || ! (mask&(1<<v)) )
            {
                dp[i+1][mask] += dp[i][mask];
            }
            else
            {
                dp[i+1][mask] += (1-p)*dp[i][mask];
                dp[i+1][mask & (~(1<<v))] += p*dp[i][mask];
            }
        }
    }

    cout<<fixed<<setprecision(10);
    for(int i = 0; i<n; i++)
    {
        ld res = 0;
        for(int mask = 0; mask < (1<<n); mask++)
        {
            if(mask & (1<<i))
                res += dp[m][mask];
        }
        cout<<res<<endl;
    }
    
    return 0;
}