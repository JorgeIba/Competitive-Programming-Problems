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
#define pb push_back

using namespace std;

const int MAXN = 3000 + 100;
const int INF = 1e9;
vector<int> adjList[MAXN];

int main () {
	fastIO();
	
    int n, m; cin>>n>>m;

    vector< pair<int,int> > edges;
    forn(i, m) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        if(u > v) swap(u, v);
        edges.pb({u, v});
    }


    auto bfs = [&](int start, int end) {
        vector<int> dist(n+1, INF);

        queue<int> q;
        q.push(start);
        dist[start] = 0;

        while(!q.empty()) {
            auto u = q.front(); q.pop();

            for(auto v: adjList[u]) {
                if(dist[v] != INF) continue;
                auto aux_u = u, aux_v = v;
                if(aux_u > aux_v) swap(aux_u, aux_v);

                if(aux_u == start && aux_v == end) continue;

                dist[v] = dist[u] + 1;
                q.push(v);            
            }
        }
        return dist;
    };


    int shortest_cycle = INF;
    for(int i = 0; i < m; i++){
        auto [u, v] = edges[i];

        auto shortest_dist = bfs(u, v)[v];
        shortest_cycle = min(shortest_cycle, shortest_dist + 1);
    }

    
    vector<int> visited(n+1); // 0 nunca lo visite, 1 estoy actualmente visitandolo, 2 terminé de visitarlo hace mucho
    vector<int> dp(n+1);
    vector<int> dist_all(n+1);

    auto dfs = [&](const auto &dfs, int u, const int &start, const int &end, int dist = 0) -> lli{
        if(u == end) {
            return dist == shortest_cycle - 1;
        }

        if(dist > dist_all[u]) return 0;

        if(visited[u] == 1) return dp[u];
        visited[u] = 1;

        lli ans = 0;
        for(auto v: adjList[u]) {
            auto aux_u = u, aux_v = v;
            if(aux_u > aux_v) swap(aux_u, aux_v);

            if(aux_u == start && aux_v == end) continue;

            ans += dfs(dfs, v, start, end, dist + 1);
        }


        return dp[u] = ans;
    };

    lli ans = 0;
    for(int i = 0; i < m; i++) {   
        auto [u, v] = edges[i];

        fill(all(visited), 0);
        fill(all(dp), 0);

        dist_all = bfs(u, v);
        

        ans += dfs(dfs, u, u, v);
    }

    // cout << ans / shortest_cycle << endl;

    cout << ans << " " << shortest_cycle << endl;

	return 0;
}