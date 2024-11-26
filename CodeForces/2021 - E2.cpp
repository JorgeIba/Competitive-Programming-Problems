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

const lli INF = 1e15;

struct DSU {
    int n;
    vector<int> parent, sz;

    DSU(int n): n(n), parent(n), sz(n, 1) {
        iota(all(parent), 0);
    }

    int root(int u) {
        return parent[u] = (parent[u] == u ? u : root(parent[u]));
    }

    bool join(int u, int v) {
        u = root(u), v = root(v);
        if(u == v) return false;
        if(sz[u] < sz[v])
            swap(u, v);

        parent[v] = u;
        sz[u] += sz[v];

        return true;
    }
};

void main_() {
    int n, m, p; cin>>n>>m>>p;
    vector<int> S(p);
    for(auto &s: S) {
        cin>>s;
        s--;
    }

    vector< tuple<int,int,int> > edges(m);
    for(auto &[w, u, v]: edges) {
        cin>>u>>v>>w;
        u--, v--;
    }

    vector< vector<pair<int,int>> > adjList(n);

    DSU D(n);

    sort(all(edges));
    for(auto [w, u, v]: edges) {
        if(D.root(u) == D.root(v)) continue;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});

        D.join(u, v);
    }

    vector< vector<int> > cost(n, vector<int>(n));
    auto dfs = [&](const auto &dfs, int u, int biggest, const int start, int p = -1) -> void {
        cost[start][u] = cost[u][start] = biggest;

        for(auto [v, w]: adjList[u]) {
            if(v == p) continue;
            dfs(dfs, v, max(biggest, w), start, u);
        }
    };

    for(auto s: S) {
        dfs(dfs, s, 0, s, -1);
    }

    vector< set<pair<lli,int>> > best_per_node(n);
    vector< lli > total_cost(n);
    for(auto s: S) {
        for(auto start: S) {
            best_per_node[s].insert({cost[start][s], s});
            total_cost[start] += cost[start][s];
        }
    }
    
    lli ans = 0;
    for(int k = 1; k <= n; k++) {
        pair<lli,int> best_save = {-1, -1};
        for(auto start: S) {
            best_save = min(best_save, {total_cost[start], start});
        }

        auto [best_cost, best_start] = best_save;
        ans += best_cost;
        total_cost[best_start] = INF;

        for(auto s: S) {
            auto itr = best_per_node[s].find({cost[start]});
        }



        cout << ans << " ";
    }

    cout << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

