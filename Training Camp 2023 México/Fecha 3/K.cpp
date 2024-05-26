#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


const int MAXN = 2e5+100;

vector<int> adjList[MAXN];
vector<int> adjTree[MAXN];

int low[MAXN], disc[MAXN];
int Time = 1;

set< pair<int,int> > bridges;

void dfsAPB(int u, int p) {
    int nup = 0;
    low[u] = disc[u] = ++Time;
    for (int &v : adjList[u]) {
        if (v == p && !nup++) continue;
        if (!disc[v]) {
        dfsAPB(v, u);
        if (disc[u] < low[v]) bridges.insert({min(u,v), max(u,v)});
        low[u] = min(low[u], low[v]);
        } else
        low[u] = min(low[u], disc[v]);
    }
}

struct UnionFind{
    vector<int> parent, sizes;

    UnionFind() {}
    UnionFind(int n): parent(n), sizes(n) {
        forn(i, n) parent[i] = i;
    }

    int root(int u) {
        return parent[u] = (parent[u] == u ? u : root(parent[u]));
    }

    void join(int u, int v){
        u = root(u);
        v = root(v);

        if(u == v) return;

        if(sizes[u] > sizes[v]) swap(u, v);

        sizes[v] += sizes[u];
        parent[u] = v;
    }
};



struct LCA_T{
    const static int maxLOG = 20;
    int n;
    vector<int> depth, order, colors;    

    vector< vector<int> > ancestors;

    template<class G>
    LCA_T(int n, const G &adjList): n(n), depth(n), colors(n) {
        ancestors.assign(n, vector<int>(maxLOG));
        for(int i = 0; i < n; i++) ancestors[i][0] = i;

        int color = 1;
        forn(i, n)
            if(!colors[i])
                dfs(i, adjList, color++);
        prec();
    }

    template<class G>
    void dfs(int u, const G &adjList, int color, int p = -1) {
        colors[u] = color;
        order.push_back(u);
        for(auto v: adjList[u]){
            if(v == p) continue;
            ancestors[v][0] = u;
            depth[v] = depth[u] + 1;

            dfs(v, adjList, color, u);
        }
    }

    void prec() {
        for(auto u: order) 
            for(int i = 1; i < maxLOG; i++) 
                ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
        order.clear();
    }

    int get_kth_parent(int u, int k){
        for(int i = maxLOG - 1; i >= 0; i--) 
            if(k & (1 << i))
                u = ancestors[u][i];
        return u;
    }

    int get_lca(int u, int v) {
        if(depth[u] > depth[v]) swap(u, v);
        v = get_kth_parent(v, depth[v] - depth[u]);

        for(int i = maxLOG-1; i >= 0; i--) {
            if(ancestors[u][i] != ancestors[v][i]) {
                u = ancestors[u][i];
                v = ancestors[v][i];
            }
        }
        return u != v ? ancestors[u][0] : u;
    }
};



int main () {
	//fastIO();
	
    int n, m, q; cin>>n>>m>>q;

    vector< pair<int,int> > edges;
    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edges.push_back({u, v});
    }

    forn(i, n){
        if(!disc[i]) dfsAPB(i, -1);
    }

    UnionFind UF(n);
    for(auto [u, v]: edges){
        if(bridges.count({min(u, v), max(u, v)})) continue;

        UF.join(u, v);
    }

    for(auto [u, v]: bridges){
        u = UF.root(u);
        v = UF.root(v);
        adjTree[u].push_back(v);
        adjTree[v].push_back(u);
    }

    LCA_T LCA(n, adjTree);

    vector< pair<int,int> > dirs(n, pair<int,int>(-2, -2)); 

    bool can = true;
    forn(i, q){
        int u, v; cin>>u>>v; u--, v--;

        u = UF.root(u);
        v = UF.root(v);

        if(u == v) continue;

        if(LCA.colors[u] != LCA.colors[v]){
            can = false;
        }

        int lca = LCA.get_lca(u, v);
        int dist_u = LCA.depth[u] - LCA.depth[lca];
        int dist_v = LCA.depth[v] - LCA.depth[lca];

        pair<int,int> dir_u = {+1, dist_u};
        pair<int,int> dir_v = {-1, dist_v};


        if(dirs[u].first == -1 && dist_u) {
            can = false;
        }
        if(dirs[v].first == +1 && dist_v) {
            can = false;
        }

        if(dist_u)
            dirs[u] = dir_u;
        if(dist_v)
            dirs[v] = dir_v;
    }

    vector<bool> visited(n);

    auto dfs_ans = [&](const auto &dfs_ans, int u, int p = -1) -> void{
        visited[u] = true;

        int dir_pos = 0, dir_neg = 0;
        if(dirs[u].first == +1) {
            dir_pos = dirs[u].second;
        } else {
            dir_neg = dirs[u].second;
        }

        for(auto v: adjTree[u]) {
            if(v == p) continue;

            dfs_ans(dfs_ans, v, u);


            auto dir_v = dirs[v];
            dir_v.second--;
            
            if(dir_v.first == +1 && dir_v.second && dir_neg > 0) can = false;

            if(dir_v.first == -1 && dir_v.second && dir_pos > 0) can = false;

            if(dir_v.first == -1){
                dir_neg = max(dir_neg, dir_v.second);
            } else if(dir_v.first == +1) {
                dir_pos = max(dir_pos, dir_v.second);
            }
        }

        if(dir_neg > 0){
            dirs[u].second = dir_neg;
            // assert(dirs[u].first != +1);
        } else if(dir_pos > 0) {
            dirs[u].second = dir_pos;
            // assert(dirs[u].first != -1);
        } else {
            dirs[u].first = -2;
        }
    };


    forn(i, n){
        auto u = UF.root(i);
        if(!visited[u])
            dfs_ans(dfs_ans, u);
    }
        


    cout << (can ? "Yes" : "No") << endl;




	return 0;
}

