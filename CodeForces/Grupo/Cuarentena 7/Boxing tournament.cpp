#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 19, maxMask = (1<<maxN);
ld dp[maxMask];


int main()
{
    fastIO();
    lli n; cin>>n;
    vector< vector<ld> > mat(n, vector<ld>(n));
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            cin>>mat[i][j];
        }
    }

    cout<<fixed<<setprecision(10);
    dp[ ((1<<n) - 1) ] = 1;
    
    for(int mask = ((1<<n) - 1) ; mask >=0; mask--)
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = i+1; j<n; j++)
            {
                ld p = mat[i][j];
                lli x = __builtin_popcountll(mask);
                if( x < 2) continue;
                ld xi = x;
                ld pr = 2 / (xi * (xi-1));
                if( (mask&(1<<i)) && (mask&(1<<j)) )
                {
                    dp[ mask & ( ~ (1<<i)  )  ] += (1-p)*dp[mask]*pr;
                    dp[ mask & (  ~(1<<j)  )  ] += (p)*dp[mask]*pr;
                }
            }
        }
    }
    
    for(int i = 0; i<n; i++)
    {
        lli mask = (1<<i);
        cout<< dp[mask] << endl;
    }
    
    return 0;
}