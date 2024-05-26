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
const lli MOD = 10007;
const lli maxN = 100010 + 10;
lli dp_best[maxN][2];
lli dp_ways[maxN][2];

lli dfs(lli u, bool on_above, lli parent) {

    lli szAdj = SZ(adjList[u]);
    if(szAdj == 1 && u != 1) {
        if(on_above)
            return 0;
        else 
            return 1;
    }

    lli &ans = dp_best[u][on_above];
    if(ans != -1) return ans;

    ans = 1e18;
    
    if(on_above) {
        lli si = 1, no = 0;

        for(auto v: adjList[u]) {
            if(v == parent) continue;

            si += dfs(v, true, u);   
        }

        for(auto v: adjList[u]) {
            if(v == parent) continue;

            no += dfs(v, false, u);
        }
        ans = min(si, no);
    } else {

        lli si = 1;
        for(auto v: adjList[u]) {
            if(v == parent) continue;
            
            si += dfs(v, true, u);
        }
        ans = si;
    }

    return ans;
}


lli dfs_ways(lli u, bool on_above, lli parent) {
    lli szAdj = SZ(adjList[u]);
    if(szAdj == 1 && u != 1) {
        return 1;
    }

    lli &ans = dp_ways[u][on_above];
    if(ans != -1) return ans;

    ans = 0;
    if(on_above) {
        lli si = 1, no = 0;

        for(auto v: adjList[u]) {
            if(v == parent) continue;
            si += dfs(v, true, u);   
        }

        for(auto v: adjList[u]) {
            if(v == parent) continue;
            no += dfs(v, false, u);
        }


        lli ways_si = 1, ways_no = 1;

        for(auto v: adjList[u]) {
            if(v == parent) continue;

            ways_si = (ways_si * dfs_ways(v, true, u)) % MOD;
        }

        for(auto v: adjList[u]) {
            if(v == parent) continue;

            ways_no = (ways_no * dfs_ways(v, false, u)) % MOD;
        }


        
        if(si < no) {
            ans = ways_si;
        } else if(no < si) {
            ans = ways_no;
        } else {
            ans = (ways_no + ways_si) % MOD;
        }
    } else {

        lli ways_si = 1;

        for(auto v: adjList[u]) {
            if(v == parent) continue;

            ways_si = (ways_si * dfs_ways(v, true, u)) % MOD;
        }
        
        
        ans = ways_si;
    }

    return ans;
}


void solve() {
    lli n; cin>>n;
    adjList.clear();
    adjList.resize(n+1);

    for(int i = 0; i < n-1; i++) {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    memset(dp_best, -1, sizeof(dp_best));
    memset(dp_ways, -1, sizeof(dp_ways));

    lli best = dfs(1, 1, -1);

    lli ways = dfs_ways(1, 1, -1);

    cout << best << " " << ways << endl;

}


int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

