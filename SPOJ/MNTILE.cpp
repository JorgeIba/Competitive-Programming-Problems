#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli w, h;

//lli dp[10][10][1<<10];
vector<lli> dp;

lli &at(lli i, lli j, lli profile)
{
    return dp[i*h*(1<<h) + j*(1<<h) + profile];
}

lli fun(lli i, lli j, lli profile)
{
    if(i == w)
    {
        if(profile == 0) return 1;
        return 0;
    }
    if(j == h)
    {
        return fun(i+1, 0, profile);
    }

    //lli &res = dp[i][j][profile];
    lli &res = at(i,j,profile);
    if(res != -1) return res;

    res = fun(i, j+1, profile^(1<<j) );

    if( (profile & (1<<j))  )
        return res;

    if( j+1 < h && !(profile&( 1<<(j+1) )))
        res += fun(i, j+2, profile);

    return res;
}



void solve()
{    
    cin>>w>>h;
    dp.clear();
    dp.resize( w*h*(1<<h) , -1);
    //memset(dp, -1, sizeof(dp));
    cout << fun(0,0,0) << endl;
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}