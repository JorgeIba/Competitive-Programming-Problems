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

const int MAXN = 3e5+100;

vector<int> adjList[MAXN];
vector<int> adjTree[MAXN];


int low[MAXN], disc[MAXN];
int Time = 0;

set<pair<int,int>> bridges;


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



int main () {
	fastIO();
	
    int n, m; cin>>n>>m;

    vector< pair<int,int> > edges;
    forn(i, m) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edges.push_back({u, v});
    }


    dfsAPB(0, -1);

    UnionFind UF(n);
    for(auto [u, v]: edges) {
        if(bridges.count({min(u,v), max(u, v)})) continue;

        UF.join(u, v);
    }

    for(auto [u, v]: bridges){
        u = UF.root(u);
        v = UF.root(v);
        adjTree[u].push_back(v);
        adjTree[v].push_back(u);
    }


    auto bfs = [&](int s) -> pair<int,int> {
        vector<int> dist(n, -1);
        queue<int> q; q.push(s);
        dist[s] = 0;

        while(!q.empty()){
            int u = q.front(); q.pop();

            for(auto v: adjTree[u]) {
                if(dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        auto itr = max_element(all(dist));
        return {*itr, itr - begin(dist)};
    };

    auto [dist, end_point_1] = bfs(UF.root(0));
    auto [max_dist, end_point_2] = bfs(end_point_1);


    cout << max_dist << endl;

	return 0;
}

