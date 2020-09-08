#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bitset<1026> dp[202];

int main () {
	fastIO();
    lli n, m; cin>>n>>m;

    vector< lli > a(n+1), b(m+1);
    for(int i = 1; i<=n; i++) cin>>a[i];
    for(int i = 1; i<=m; i++) cin>>b[i];

    //dp[i][mask] can i reach to "mask" processing i numbers
    dp[0][0] = true; // If you dont process any number, then you can get 0 as answer.
    for(int i = 1; i<=n; i++)
    {
        for(int j = 1; j<=m; j++)
        {
            for(int mask = 0; mask<(1<<9); mask++)
            {
                if(dp[i-1][mask] == 1) 
                {
                    dp[i][((b[j] & a[i]) | mask)] = 1; // If mask is reachable having been proccesed i-1 numbers
                                                       // then ((b[j] & a[i]) | mask) is also reachable but processing i numbers
                }
            }
        }
    }

    for(int mask = 0; mask<(1<<9); mask++)
    {
        if(dp[n][ mask ]) // The first that i find is the minimum
        {
            cout << mask << endl;
            return 0;
        }
    }



	return 0;
}