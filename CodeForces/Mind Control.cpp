#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> nums;
vector< vector< lli > > dp;

lli fun(lli L, lli R, lli m, lli k)
{
    if(m==1)
    {
        return dp[L][R] = max(nums[L], nums[R]);
    }
    if(dp[L][R] != -1) return dp[L][R];
    if(k>0)
    {
        return dp[L][R] = max(fun(L+1, R, m-1, k-1), fun(L, R-1, m-1, k-1));
    }
    else
    {
        return dp[L][R] = min(fun(L+1, R, m-1, k), fun(L, R-1, m-1, k));
    }   
}

void solve()
{
    lli n, m, k; cin>>n>>m>>k;
    dp.clear(); dp.resize(n+1, vector<lli>(n+1, -1));
    nums.clear(); nums.resize(n+1);
    forn(i, 1, n+1) cin>>nums[i];
    cout << fun(1, n, m, k) << endl;
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}