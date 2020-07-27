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
    //fastIO();
    lli m, k; cin>>m>>k;
    
    vector< lli > pilas(k);
    for(auto &x: pilas) cin>>x;

    vector< vector< lli > > dp(m+10, vector<lli> ( (1<<17) ) );

    dp[0][0] = 1;
    for(int i = 1; i<=m; i++)
    {
        for(int x = 0; x<k; x++)
        {
            lli pila = pilas[x];
            for(lli mask = 0; mask < (1<<17); mask++)
            {
                dp[ i ][ (pila ^ mask) ] += dp[i-1][mask];
            }
        }
    }
    
    cout << dp[m][0] << endl;
    return 0;
}