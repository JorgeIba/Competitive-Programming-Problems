#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n, k, MOD = 998244353;

lli dp[1001][2002][4];

lli fun(lli i, lli j, lli profile)
{
    if(i == n)
    {
        if(j == k) return 1;
        return 0;
    }
    lli &res = dp[i][j][profile];
    if(res != -1) return res;
    res = 0;
    if(profile == 0)
    {
        res = (res +  fun(i+1, j+1, 3)) % MOD;
        res = (res +  fun(i+1, j+1, 2)) % MOD;
        res = (res +  fun(i+1, j+1, 1)) % MOD;
        res = (res +  fun(i+1, j, 0)) % MOD;
    }
    else if(profile == 1)
    {
        res = (res +  fun(i+1, j, 3)) % MOD;
        res = (res +  fun(i+1, j+2, 2)) % MOD; 
        res = (res +  fun(i+1, j, 1)) % MOD;
        res = (res +  fun(i+1, j, 0)) % MOD;
    }
    else if(profile == 2)
    {
        res = (res +  fun(i+1, j, 3)) % MOD;
        res = (res +  fun(i+1, j, 2)) % MOD;
        res = (res +  fun(i+1, j+2, 1)) % MOD;
        res = (res +  fun(i+1, j, 0)) % MOD;
    }
    else
    {
        res = (res +  fun(i+1, j, 3)) % MOD;
        res = (res +  fun(i+1, j+1, 2)) % MOD;
        res = (res +  fun(i+1, j+1, 1)) % MOD;
        res = (res +  fun(i+1, j+1, 0)) % MOD;
    }
    return res%MOD;
}



int main()
{
    //fastIO();
    memset(dp, -1, sizeof(dp));
    cin>>n>>k;

    //cout<< fun(1,1,0) << " " << fun(1,2,1) <<" "<< fun(1,2,2) << " "<< fun(1,1,3)<<endl;
    cout<< (fun(1,1,0) + fun(1,2,1) + fun(1,2,2) + fun(1,1,3))%MOD << endl;

    return 0;
}