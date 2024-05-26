#include<bits/stdc++.h>
#define lli long long int
#define ld long double
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lli> vlli;

int n, m, p, l;
const int maxn = 2e5 + 10;
vector<int> adj[maxn];
map<pii, set<int>> aux;
set<pii> banned;

const lli inf = 1e15;
vector<lli> dijkstra(int s) {
  vector<lli> dis(n, inf);
  dis[s] = 0;
  priority_queue<pair<lli, int>, vector<pair<lli,int>>, greater<pair<lli, int>> > pq;
  pq.push({0, s});
  while(!pq.empty()) {
    auto[dist_u, u] = pq.top(); pq.pop();
    if(dist_u > dis[u]) continue;

    for(int v : adj[u]) {
      lli w = 1;
      int uu = u, vv = v;
      if(vv < uu) swap(uu, vv);
      lli wait = 0;
      // cout << "trying: " << uu <<  ' ' << vv << endl;
      if(banned.count({uu, vv})) continue;
      while(aux[{uu, vv}].count((dis[u] + wait) % l)) wait++;
      if(dis[u] + w + wait < dis[v]) {
        dis[v] = dis[u] + w + wait;
        pq.push({dis[v], v});
      }
    }
  }
  return dis;
}

int main() {
  fastIO();
  cin >> n >> m >> p >> l;
  int u, v;
  forn(i,m) {
    cin >> u >> v;
    u--; v--;
    adj[u].pb(v);
    adj[v].pb(u);
    aux[{min(u,v), max(u,v)}] = set<int>();
  }
  forn(i,p) {
    vi aux_path(l);
    for(auto& x : aux_path) {
      cin >> x;
      x--;
    }
    forn(i,l) {
      int u = aux_path[i], v = aux_path[(i + 1) % l];
      if(u > v) swap(u,v);
      aux[{u,v}].insert(i);
    }
  }
  for(auto x : aux) {
    if(x.second.size() == l)
      banned.insert(x.first);
  }
  /*
  for(auto x : aux) {
    cout << x.first.first << ' ' << x.first.second << ":" << endl;
    for(int a : x.second) cout << a << ' '; cout << endl;
  }
  cout << "--------------\n";
  */
  // cout << "BANNED" << endl;
  // for(auto x : banned) cout << x.fi << ' ' << x.se << endl;
  int s, t;
  cin >> s >> t;
  s--; t--;
  auto dis = dijkstra(s);
  if(dis[t] >= inf) cout << "IMPOSSIBLE" << endl;
  else cout << dis[t] << endl;
  return 0;
}
 