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


const int MAXN = 1e5 + 100;

vector< pair<int,int> > adjList[MAXN];
map< pair<int,int>, int > edge_to_idx;

const lli INF = 1e15;
pair< vector<lli>, vector<int> > dijkstra(int s, int n) {
    vector< lli > dist(n, INF);
    vector< int > parent(n, -1);

    priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 
    dist[s] = {0};
    pq.push({0, s});

    while(!pq.empty()) {
        auto [d1, u] = pq.top(); pq.pop();
        if(d1 > dist[u]) continue;
        
        for(auto [v, t]: adjList[u]) {
            if(d1 + t < dist[v]) {
                dist[v] = d1 + t;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {dist, parent};
}


vector< array<lli,2> > dijkstra2(int s, int n, const set<int> edges) {
    vector< array<lli,2> > dist(n, {INF, INF});

    priority_queue< tuple<int, int, int>, vector<tuple<int,int, int>>, greater<tuple<int,int, int>>> pq; // alv la declaracion
    dist[s] = {0, INF};
    pq.push({0, 0, s});

    while(!pq.empty()) {
        auto [d1, world, u] = pq.top(); pq.pop();

        if(d1 > dist[u][world]) continue;
        
        for(auto [v, t]: adjList[u]) {
            int idx_edge = edge_to_idx[{min(u,v), max(u,v)}];
            if(edges.count(idx_edge) && world == 0) { // Sigo teniendo las mismas aristas
                if(d1+t < dist[v][0]) {
                    dist[v][0] = d1 + t;
                    pq.push({d1+t, 0, v});
                }
            } else {
                if(d1 + t < dist[v][1]) {
                    // cout << u << " --> " << v << " = " << d1 << " ---- " << t << " --- " << world << endl;
                    dist[v][1] = d1+t;
                    pq.push({d1+t, 1, v});
                }
            }
        }
    }

    return dist;
}



int main () {
	// fastIO();
    int n, m; cin>>n>>m;

    forn(i, m) {
        int u, v, t; cin>>u>>v>>t;
        u--, v--;
        adjList[u].push_back({v, t});
        adjList[v].push_back({u, t});
        edge_to_idx[{min(u,v), max(u, v)}] = i;
    }

    auto [dist, parents] = dijkstra(0, n);
    if(parents[n-1] == -1) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> path;
    set<int> edges;
    int curr = n-1;
    while(curr != 0) {
        path.push_back(curr);
        edges.insert(edge_to_idx[{min(curr,parents[curr]), max(curr,parents[curr])}]);
        curr = parents[curr];
    }


    lli opt1 = INF;
    for(auto [v, t]: adjList[0]) {
        int id_edge = edge_to_idx[{0, v}];
        if(edges.count(id_edge)) continue;
        // cout << v << " --- " << t << endl;
        opt1 = 2*t + 2*dist[n-1];
    }


    auto dist_2 = dijkstra2(0, n, edges);
    lli opt2 = dist_2[n-1][1] + dist[n-1];

    // debugg(opt1);
    // debugg(opt2);

    lli ans = min(opt1, opt2);
    if(ans >= INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }







	return 0;
}

