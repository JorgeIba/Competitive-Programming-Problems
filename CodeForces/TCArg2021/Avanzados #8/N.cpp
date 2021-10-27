#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


map<pair<lli,lli> ,lli> dp;
vector<lli> longs, costs;
const lli INF = 1e18;
lli n;

lli fun(lli idx, lli gcd)
{
    if(idx == n)
    {
        if(gcd == 1) return 0;
        else return INF;
    }

    
    if(dp.count({idx, gcd})) return dp[{idx, gcd}];

    return dp[{idx, gcd}] = min(fun(idx+1, gcd), fun(idx+1, __gcd(gcd, longs[idx])) + costs[idx]  );
}



int main () {
	//fastIO();
    cin>>n;
    
    longs.resize(n);
    costs.resize(n);

    for(auto &x: longs) cin>>x;
    for(auto &x: costs) cin>>x;


    lli ans = fun(0,0);
    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;

	return 0;
}

