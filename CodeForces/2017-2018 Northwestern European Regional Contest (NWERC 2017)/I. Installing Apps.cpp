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

lli n, k;
vector< tuple<lli,lli,lli> > apps;

bool compare(tuple<lli,lli,lli> a, tuple<lli,lli,lli> b)
{
    return get<0>(a) - get<1>(a) > get<0>(b) - get<1>(b);
}

const lli maxN = 505, maxK = 10005, INF = 1e16;
lli dp[maxN][maxK];

lli f(lli idx, lli w)
{
    if(w < 0) return -INF;
    if(idx == n) return 0;

    if(dp[idx][w] != -1) return dp[idx][w];

    auto app = apps[idx];
    lli tomar = -INF, noTomar = 0;
    if(get<0>(app) <= w) tomar = f(idx+1, w - get<1>(app)) + 1;
    noTomar = f(idx+1, w);
    return dp[idx][w] = max(tomar, noTomar);
}

void g(lli idx, lli w, vector<lli> &ans)
{
    if(w < 0) return;
    if(idx == n) return;

    auto app = apps[idx];
    lli tomar = -INF, noTomar = 0;
    if(get<0>(app) <= w) tomar = f(idx+1, w - get<1>(app)) + 1;
    noTomar = f(idx+1, w);
    if(tomar > noTomar)
    {
        ans.push_back(get<2>(app));
        g(idx+1, w - get<1>(app), ans);
    } 
    else
    {
        g(idx+1, w,  ans);
    }

    return ;
}

int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));
    cin>>n>>k;
    apps.resize(n);
    for(int i = 0; i<n; i++)
    {
        lli x, y; cin>>x>>y;
        apps[i] = {x,y,i+1};
    }
    sort(all(apps), compare);

    cout << f(0, k) << endl;

    vector<lli> ans;
    g(0, k, ans);
    for(auto x: ans) cout << x << " ";
    
	return 0;
}