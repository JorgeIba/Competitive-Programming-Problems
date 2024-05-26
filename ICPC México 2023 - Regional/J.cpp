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


const int MAXN = 1e5 + 100;
const int LOG = 19;

int parentCentroid[MAXN];
int stsz[MAXN];
int depth[MAXN];

int ancestor[MAXN][LOG];

vector<int> adjList[MAXN];
array<int,2> rangess[MAXN];
int Time = 0;


bool vis[MAXN];



void dfs_prec(int u, int p = 0){

    ancestor[u][0] = p;
    for(int i = 1; i < LOG; i++){
        ancestor[u][i] = ancestor[ancestor[u][i-1]][i-1];
    }

    stsz[u] = 1;
    rangess[u][0] = Time++;
    for(auto v: adjList[u]){
        if(v == p) continue;
        depth[v] = depth[u] + 1;

        dfs_prec(v, u);

        stsz[u] += stsz[v];
    }
    rangess[u][1] = Time-1;
}

bool is_above(int u, int v){
    return rangess[u][0] <= rangess[v][0] && rangess[v][1] <= rangess[u][1];
}

int lca(int u, int v){
    if(is_above(u, v)) return u;
    if(is_above(v, u)) return v;

    for(int i = LOG-1; i >= 0; i--){
        if(!is_above(ancestor[u][i], v)) {
            u = ancestor[u][i];
        }
    }
    return ancestor[u][0];
}


int centrDesc(int root) {
    int sz = 1;
    for (auto v : adjList[root])
        if (!vis[v])
            sz += stsz[v];
    while (true) {
        int cent = -1;
        for (auto v : adjList[root]) {
            if (!vis[v] && 2 * stsz[v] > sz)
                cent = v;
        }
        if (cent == -1)
            break;
        stsz[root] = sz - stsz[cent];
        root = cent;
    }
    vis[root] = true;
    for (auto v : adjList[root])
        if (!vis[v])
            parentCentroid[centrDesc(v)] = root;

    return root;
}


int dist(int u, int v){
    return depth[u] + depth[v] - 2*depth[lca(u, v)];
}


pair<int,int> values[MAXN];
const int INF = 1e9;
int query(int start) {
    int curr = start;
    pair<int,int> ans = {INF, INF};
    while(true) {
        pair<int,int> opt = values[curr];
        opt.first += dist(start, curr);
        ans = min(ans, opt);
        if(parentCentroid[curr] == -1) break;
        curr = parentCentroid[curr];
    }

    return ans.second;
}

void update(int start) {
    int curr = start;
    while(true){
        values[curr] = min(values[curr], {dist(start, curr), start});
        if(parentCentroid[curr] == -1) break;
        curr = parentCentroid[curr];
    }
}


int main () {
	fastIO();

    int n; cin>>n;
    forn(i, n-1) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    fill(parentCentroid, parentCentroid+n, -1);
    dfs_prec(0);
    centrDesc(0);

    forn(i, n) values[i] = {INF, INF};
    vector<int> ans(n);
    for(int i = n-1; i >= 0; i--){
        auto x = query(i);
        if(x == INF) ans[i] = i;
        else ans[i] = x;

        update(i);
    }

    for(auto x: ans) cout << x+1 << " ";
    cout << endl;


	return 0;
}

