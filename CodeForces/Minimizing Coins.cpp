#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 1e6 + 10, INF = 1e18;

int main()
{
    //fastIO();
    lli n, target; cin>>n>>target;
    vector<lli> coins(n);
    vector< lli > dp(target+2, INF);
    for(auto &x: coins)
    {
        cin>>x;
        dp[x] = 1;
    }
    sort(coins.rbegin(), coins.rend());
    dp[0] = 0;
    for(int i = 0; i<n; i++)
    {
        lli c = coins[i];
        lli aux = c;
        while(aux+c <= target+1)
        {
            dp[aux+c] = min(dp[aux+c], 1 + dp[aux]);
            aux += c;
        }
    }
    if(dp[target] != INF) //TODO pendiende
    {
        cout<<dp[target]<<endl;
    }
    else
    {
        cout<<-1<<endl;
    }
    

    return 0;
}