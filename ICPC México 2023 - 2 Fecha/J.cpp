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

const int MAXN = 1e5+100;

vector<int> adjList[MAXN];
vector<int> adjTree[MAXN];



int Time = 0;
int disc[MAXN], low[MAXN], isAp[MAXN];
set< pair<int,int> > bridges;

int dfsAPB(int u, int p) {
  int ch = 0, nup = 0;
  low[u] = disc[u] = ++Time;
  for (int &v : adjList[u]) {
    if (v == p && !nup++) continue;
    if (!disc[v]) {
      ch++, dfsAPB(v, u);
      if (disc[u] <= low[v]) isAp[u]++;
      if (disc[u] < low[v]) bridges.insert({min(u, v), max(u, v)});
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], disc[v]);
  }
  return ch;
}


int main () {
	//fastIO();
	
    int n, m, q; cin>>n>>m>>q;


    vector< pair<int,int> > edges;
    forn(i, m) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edges.push_back({min(u, v), max(u, v)});
    }

    dfsAPB(0, -1);

    vector<int> banned(n);
    for(auto [u, v]: edges) {
        if(bridges.count({u, v})) continue;
        
        banned[u] = banned[v] = 1;
    }   

    
    for(auto [u, v]: bridges) {
        if(banned[u] || banned[v]) continue;
        adjTree[u].push_back(v);
        adjTree[v].push_back(u);
    }

    vector<int> colors(n);

    auto dfs_paint = [&](const auto &dfs_paint, int u, int color, int p) -> void{
        colors[u] = color;

        for(auto v: adjTree[u]) {
            if(v == p) continue;
            dfs_paint(dfs_paint, v, color, u);
        }
    };

    int color = 1;
    forn(i, n) {
        if(banned[i] || colors[i]) continue;

        dfs_paint(dfs_paint, i, color, -1);
        color++;
    }


    while(q--){
        int u, v; cin>>u>>v; u--, v--;
        if(banned[u] || banned[v]) {
            cout << "NO" << endl;
            continue;
        }

        if(colors[u] == colors[v]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }





	return 0;
}

