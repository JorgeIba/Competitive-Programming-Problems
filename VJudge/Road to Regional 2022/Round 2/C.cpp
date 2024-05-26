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


vector<vector<lli>> adjList;

const lli maxN = 1e5;
lli dp[maxN][3];


bool dfs(int u, bool turn) {
    int sz = adjList[u].size();
    if(!sz) {
        return false;
    }

    
    lli &ans = dp[u][turn];
    if(ans != -1) return ans;
    
    ans = false;
    for(auto v: adjList[u]) {
        auto ans_v = dfs(v, !turn);
        if(!ans_v)
            ans = true;
    }

    return ans;
}


void solve(int test) {
    lli n, m, x; cin>>n>>m>>x;

    adjList.clear();
    adjList.resize(n+1);

    for(int i = 0; i <m ; i++) {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
    }

    memset(dp, -1, sizeof(dp));
    bool ans = dfs(x, 0);

    cout << "Case " << test << ": ";
    if(ans) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

}



int main () {
	fastIO();

    lli t; cin>>t; 

    for(int i = 1; i <= t; i++) {
        solve(i);
    }

	return 0;
}

