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


int main () {
	fastIO();

    lli n, k, m; cin>>n>>k>>m;
    vector< vector<lli> > adjList(n+1);
    for(int i = 0; i<m; i++)
    {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
    }

    vector<lli> order(n*k);
    for(auto &x: order) cin>>x;

    map<lli,lli> last;
    vector<lli> ans(n*k);
    for(int i = 0; i<n*k; i++)
    {
        ans[i] = ++last[order[i]];
    }

    for(auto x: ans) cout << x << " ";


	return 0;
}

