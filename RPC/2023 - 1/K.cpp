#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;

typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int MAXN = 2e5 + 5;
const int LOG = 20;

int n, m;
vi adj[MAXN];
vi adjt[MAXN];
int parent[MAXN];
int level[MAXN];
int ancestor[MAXN][LOG];

void dfs(int u){
	for(auto v:adjt[u]){
		if(v != parent[u]){
			parent[v] = u;
			level[v] = level[u] + 1;
			dfs(v);
		}
	}
}

void build(int root){
	memset(ancestor, -1, sizeof(ancestor));
	parent[root] = root;
	dfs(root);
	forn(u, n)
		ancestor[u][0] = parent[u];
	for(int i = 1; (1 << i) <= n; i++){
		forn(u, n)
			ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
	}
}

int lca(int u, int v){
	if(level[u] < level[v]) swap(u, v);
	int lg;
	for(lg = 1; (1 << lg) <= level[u]; lg++);
	lg--;
	for(int i = lg; i >= 0; i--){
		if(level[u] - (1 << i) >= level[v])
			u = ancestor[u][i];
	}
	if(u == v) return u;
	for(int i = lg; i >= 0; i--){
		if(ancestor[u][i] != -1 && ancestor[u][i] != ancestor[v][i]){
			u = ancestor[u][i];
			v = ancestor[v][i];
		}
	}
	return parent[u];
}

int get_dist(int u, int v){
	/* cout << var(u) << ' ' << var(v) << " lca: " << lca(u, v) << endl; */
	return level[u] + level[v] - 2 * level[lca(u, v)];
}

vi bfs(int u){
	vi dist(n, -1);
	queue<int> Q;
	Q.push(u);
	dist[u] = 0;
	while(!Q.empty()){
		u = Q.front();
		Q.pop();
		for(auto v:adj[u]){
			if(dist[v] == -1){
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
	return dist;
}

int main () {
	fastIO();
	cin >> n >> m;
	forn(i, m){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	auto dist = bfs(0);
	/* cout << "bfs" << endl; */
	/* forn(u, n) cout << var(u) << ' ' << dist[u] << endl; */
	vi path;
	set<int> used;
	set<pii> available;
	path.pb(0);
	used.insert(0);
	auto add = [&](int u){
		int p = n;
		for(auto v:adj[u]){
			if(used.count(v)){
				if(dist[v] + 1 == dist[u])
					p = min(p, v);
			}else{
				available.insert({dist[v], v});
			}
		}
		return p;
	};
	add(0);
	forn(i, n - 1){
		auto aux = *available.begin();
		auto p = add(aux.se);
		used.insert(aux.se);
		path.pb(aux.se);
		adjt[p].pb(aux.se);
		/* cout << "edge: " << p << ' ' << aux.se << endl; */
		available.erase(aux);
	}
	/* cout << "path" << endl; */
	/* for(auto u:path) cout << u << ' '; cout << endl; */
	build(0);
	/* cout << "build" << endl; */
	lli ans = 0;
	forr(i, 1, SZ(path) - 1){
		/* cout << "aux: " << get_dist(path[i - 1], path[i]) << endl; */
		ans += get_dist(path[i - 1], path[i]);
	}
	cout << ans << endl;
	return 0;
}

