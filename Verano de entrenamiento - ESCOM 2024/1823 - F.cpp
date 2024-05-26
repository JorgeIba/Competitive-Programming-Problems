#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

const int MOD = 998244353;
const int MAXN = 2e5 + 100;

vector<int> adjList[MAXN];

int depth[MAXN];
int parent[MAXN];

void dfs_1(int u, int p) {
    parent[u] = p;
    for(auto v: adjList[u]) {
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        dfs_1(v, u);
    }
}

int mark[MAXN];
int ans[MAXN];
int last_wey[MAXN];

void dfs_2(int u, int last_ancestor, int p) {
    if(mark[u]) last_ancestor = u;

    // ans[u] = 1LL * SZ(adjList[u]) * depth[u] % MOD;
    // ans[u] = SZ(adjList[u]);
    // prob[u] = depth[last_ancestor] / depth[u] % MOD;
    last_wey[u] = last_ancestor;
    for(auto v: adjList[u]) {
        if(v == p) continue;
        dfs_2(v, last_ancestor, u);
    }
}


int main () {
	// fastIO();


    int n, s, t; cin>>n>>s>>t; s--, t--;
    forn(i, n-1) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs_1(t, -1);

    int curr = s;
    while(curr != t) {
        mark[curr] = 1;
        curr = parent[curr];
    }

    dfs_2(t, t, -1);
    for(int i = 0; i < n; i++) {
        cout << (i == t ? 1 : 1LL * SZ(adjList[i]) * depth[last_wey[i]] % MOD) << " ";
    }


	return 0;
}

