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

const int MAXN = 1e6+100;

vector<int> adjList[MAXN];
vector<int> adjTree[MAXN];

int dist[MAXN];
int disc[MAXN], low[MAXN];
int Time = 1;
set< pair<int,int> > bridges;

int dfsAPB(int u, int p=-1) {
  int ch = 0, nup = 0;
  low[u] = disc[u] = ++Time;
  for (int &v : adjList[u]) {
    if (v == p && !nup++) continue;
    if (!disc[v]) {
      ch++, dfsAPB(v, u);
      if (disc[u] < low[v]) bridges.insert({min(u, v), max(u, v)});
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], disc[v]);
  }
  return ch;
}

struct UnionFind {
  int n;
  vector<int> dad, size;
  UnionFind(int N) : n(N), dad(N), size(N, 1) {
    while (N--) dad[N] = N;
  }
  
  int root(int u) {
    if (dad[u] == u) return u;
    return dad[u] = root(dad[u]);
  }

  void join(int u, int v) {
    int Ru = root(u), Rv = root(v);
    if (Ru == Rv) return;
    if (size[Ru] > size[Rv]) swap(Ru, Rv);
    --n, dad[Ru] = Rv;
    size[Rv] += size[Ru];
  }
};

bool visited[MAXN];

int main () {
	//fastIO();

    int n, m; cin>>n>>m;

    vector< pair<int,int> > edges;
    forn(i, m){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edges.push_back({u, v});
    }

    forn(i, n){
        if(visited[i]) continue;
        dfsAPB(i);
    }

    UnionFind UF(n);
    for(auto [u, v]: edges){
        if(bridges.count({min(u, v), max(u, v)}))
            continue;

        UF.join(u, v);    
    }

    for(auto [u, v]: bridges){
        u = UF.root(u);
        v = UF.root(v);

        adjTree[u].push_back(v);
        adjTree[v].push_back(u);
    }

    
    auto bfs = [&](int s, const vector<int> &comp) {
        for(auto u: comp)
            dist[u] = -1;

        queue<int> q;
        q.push(s);
        dist[s] = 0;
        while(!q.empty()){
            auto u = q.front(); q.pop();
            for(auto v: adjTree[u]){
                if(dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        int max_v = s;
        for(auto v: comp){
            if(dist[v] > dist[max_v])
                max_v = v;
        }
        return max_v;
    };

    fill(visited, visited+n, 0);
    auto dfs = [&](const auto &dfs, int u, vector<int> &comp, int p = -1) -> void {
        visited[u] = 1;
        comp.push_back(u);

        for(auto v: adjTree[u]){
            if(v == p) continue;
            dfs(dfs, v, comp, u);
        }
    };

    vector< vector<int> > comps;
    forn(i, n){
        if(visited[UF.root(i)]) continue;
        vector<int> comp;
        dfs(dfs, UF.root(i), comp);
        comps.push_back(comp);
    }


    int ans = 0;
    for(const auto &comp: comps){
        auto end_point = bfs(comp[0], comp);
        auto farthets = bfs(end_point, comp);
        ans += dist[farthets];
    }

    cout << ans + SZ(comps) - 1 << endl;



	return 0;
}
