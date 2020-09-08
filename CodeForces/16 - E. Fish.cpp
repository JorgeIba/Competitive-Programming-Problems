#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 19, INF = 1e18;
ld dp[(1<<maxN)];
ld mat[maxN][maxN];

int main()
{
    //fastIO();
    lli n; cin>>n;
    forn(i,0,n) forn(j,0,n) cin>>mat[i][j];

    dp[(1<<n) - 1] = 1;
    for(int mask = (1<<n) - 1; mask>=0; mask--)
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = i+1; j<n; j++)
            {
                lli alive = __builtin_popcount(mask);
                lli cr = alive*(alive-1) / 2;
                if(!cr) continue;
                if( mask&(1<<i)  &&  mask&(1<<j))
                {
                    dp[ mask ^ (1<<j)  ] += (ld)mat[i][j]*dp[mask]/cr;
                    dp[ mask ^ (1<<i)  ] += (ld)mat[j][i]*dp[mask]/cr;
                }
            }
        }
    }
    cout<<fixed<<setprecision(10);
    for(int i = 0; i<n; i++)
    {
        cout<< dp[1<<i] <<" ";
    }


    return 0;
}