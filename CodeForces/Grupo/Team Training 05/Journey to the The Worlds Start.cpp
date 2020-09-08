#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

lli n, t;
vector< lli > cost;
vector< lli > times;
vector< lli > ST;
const lli INF = 1e18;

//11
lli query(lli l, lli r) //Node could be just an integer
{
    lli res = INF;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1) res = min(res, ST[l++]);   
        if(~r&1) res = min(ST[r--],res);
    }
    return res;
}
//10
void update(int index, lli value)
{
    index+=n;
    ST[index] = value;
    for(; index; index>>=1)
    {
        ST[index>>1] = min(ST[index], ST[index^1]);
    }
}


bool check(lli r)
{
    ST.clear(); ST.resize(2*(n+5), INF);
    vector< lli > dp(n+5, INF);
    dp[0] = 0; //dp[i] cuanto cuesta llegar de i a n
    update(n, 0);
    for(int i = n-1; i>=1; i--)
    {
        lli q =  query(i+1, min(i+r, n));
        //cout << q << endl;
        dp[i] = times[i] + q;
        update(i, dp[i]);
    }
    //cerr << dp[1] << endl;
    if(dp[1]<=t) return true;
    return false;
}

int main () {
	fastIO();
    ifstream cin("journey.in");
	ofstream cout("journey.out");
    cin>>n>>t;
    t -= (n-1);
    cost.resize(n+1, 0);
    times.resize(n+1, 0);
    for(int i = 1; i<=n-1; i++) cin>>cost[i];
    for(int i = 2; i<=n-1; i++) cin>>times[i];

    lli l = 1, r = n-1, res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            res = mid;
            r = mid - 1;
        }
        else 
        {
            l = mid + 1;
        }
    }
    lli ans = INF;
    for(int i = res; i<=n-1; i++)
    {
        ans = min(ans, cost[i]);
    }
    cout << ans << endl;


	return 0;
}