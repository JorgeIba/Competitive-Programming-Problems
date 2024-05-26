#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define pb push_back
#define endl '\n'

using namespace std;


void dfs(int u, vector<vector<int>>& adj, vector<bool>& vis) {
  vis[u] = true;
  for(int v : adj[u]) {
    if(!vis[v]) dfs(v, adj, vis);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  vector<int> ids;
  vector<vector<int>> adj, adj_inv;
  cin >> n;
  adj.resize(1010);
  adj_inv.resize(1010);

  forn(i,n) {
    int u, x;
    cin >> u >> x;
    forn(j,x) {
      int v;
      cin >> v;
      adj[u].pb(v);
      adj_inv[v].pb(u);
    }
    ids.pb(u);
  }
  vector<bool> vis_norm(1010), vis_inv(1010);

  dfs(0, adj, vis_norm);
  dfs(0, adj_inv, vis_inv);

  // for(auto v : vis_norm) cout << v << ' '; cout << endl;
  // for(auto v : vis_inv) cout << v << ' '; cout << endl;
  vector<int> trapped, unreacheable;

  for(int x : ids) {
    if(vis_inv[x] && vis_norm[x]) continue;
    if(!vis_inv[x]) trapped.pb(x);
    if(!vis_norm[x]) unreacheable.pb(x);
  }
  if(trapped.size() == 0 && unreacheable.size() == 0) cout << "NO PROBLEMS" << endl;
  else {
    for(int x : trapped) cout << "TRAPPED " << x << endl;
    for(int x : unreacheable) cout << "UNREACHABLE " << x << endl;
  }
  return 0;
}
