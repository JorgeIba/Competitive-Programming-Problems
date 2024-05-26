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
int low[MAXN], disc[MAXN];
int Time = 1;

vector<pair<int,int>> bridges;

int dfsAPB(int u, int p=-1) {
  int ch = 0, nup = 0;
  low[u] = disc[u] = ++Time;
  for (int &v : adjList[u]) {
    if (v == p && !nup++) continue;
    if (!disc[v]) {
      ch++, dfsAPB(v, u);
      if (disc[u] < low[v]) bridges.push_back({u, v});
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], disc[v]);
  }
  return ch;
}

vector< pair<int,int> > ans;


void dfs_ans(int u, int p = -1){
    disc[u] = Time++;

    for(auto v: adjList[u]){
        if(v == p) continue;

        if(disc[v]) {
            if(disc[v] < disc[u])
                ans.push_back({u, v});
            continue;
        } 

        ans.push_back({u, v});
        dfs_ans(v, u);
    }
}


int main () {
	//fastIO();

    int n, m; cin>>n>>m;
    
    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    dfsAPB(0);

    if(!bridges.empty()) {
        cout << 0 << endl;
        return 0;
    }

    fill(disc, disc+n, 0);
    Time = 1;
    dfs_ans(0);

    for(auto [u, v]: ans) cout << u+1 << " " << v+1 << endl;


	return 0;
}

