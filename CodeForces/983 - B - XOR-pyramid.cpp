#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli total = 0;
lli dp[5005][5005];
vector<lli> nums;

lli fun(lli L, lli R)
{
    if(L == R) return nums[L];

    lli &res = dp[L][R];
    if( res != -1) return res;

    res = max( fun(L+1, R) ^ nums[L], fun(L, R-1) ^ nums[R] );

    return res;
}

int main()
{
    //fastIO();
    lli n; cin>>n;
    nums.resize(n);
    for(auto &x: nums)
    {
        cin>>x;
        //total ^= x;
    }
    //cout << fun(0, n-1) << endl;;

    //vector< vector< lli > > dp(n, vector<lli>(n));
    //dp[L][R] -> mejor XOR en L y R
    //dp[L][R] -> 
    
 
    lli q; cin>>q;
    while(q--)
    {
        lli l, r; cin>>l>>r;
        cout << dp[l][r] << endl;
    }


    return 0;
}