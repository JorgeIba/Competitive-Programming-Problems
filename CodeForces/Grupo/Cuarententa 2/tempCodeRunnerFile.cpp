#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

//map<lli,lli> mp; //get fr
//set< pair<lli,lli> > getLH; // Get higher and lower


void update(lli x, map<int,int> &mp, set<pair<int,int>> &getLH)
{
    lli fr = mp[x];
    if( getLH.count({fr, x}) )
    {
        getLH.erase({fr,x});
    }
    mp[x]++;
    getLH.insert( {mp[x], x} );
}

lli getCost( set< pair<int,lint> > getLH )
{
    lli maximo = (*getLH.rbegin()).second;
    lli minimo = (*getLH.begin()).second;
    return maximo - minimo;
}

const lli INF = 1e18;

map<int,int> mp;
set<pair<int,int>> getLH;

int main()
{
    fastIO();
    lli n, K; cin>>n>>K;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }    

    vector< vector<lli> > dp(n+1, vector<lli>(K+1, -INF));

    for(int i = n-1; i>=0; i--)
    {
        mp.clear(); getLH.clear();
        for(int j = i; j<n; j++ )
        {
            update(nums[j], mp, getLH);
        }
        dp[i][1] = getCost(getLH);
    }   

    
    for(int i = n-1; i>=0; i--)
    {
        mp.clear(); getLH.clear();
        for(int j = i; j<n; j++ )
        {
            update(nums[j], mp, getLH);
            for(int k = 2; k<=K; k++)
            {
                dp[i][k] = max(dp[i][k], getCost(getLH) +   (j<n-1? dp[j+1][k-1] : 0 ) );
            }
        }
    }   

    cout<<dp[0][K]<<endl;
    return 0;
}