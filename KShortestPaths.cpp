#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;
typedef pair<lli,lli> pll;

struct Edge{
    lli to, cost;
    Edge *rev;

    Edge(lli to, lli cost): to(to), cost(cost) {}
};

vector< vector<Edge*> > adjList, reversedAdjList;
void addEdge(int u, int v, int c) {
    Edge* uv = new Edge(v, c);
    Edge* vu = new Edge(u, c);

    uv->rev = vu; vu->rev = uv;

    adjList[u].push_back(uv);
    reversedAdjList[v].push_back(vu);
}

pair< vector<lli>, vector<Edge*> > dijkstra_best_edge(lli from)
{
    int n = adjList.size();
    vector<lli> dist( n, 1e18 ); // INF
    vector< Edge* > best_edge(n);

    priority_queue< pll, vector<pll>, greater<pll> > pq;
    pq.push({0,from}); // {costo, nodo}
    dist[from] = 0;
    while(!pq.empty())
    {
        lli u = pq.top().second; pq.pop();
        for(Edge* E: reversedAdjList[u]){
            if(dist[u] + E->cost < dist[E->to]){
                dist[E->to] = dist[u] + E->cost;
                best_edge[E->to] = E->rev; 
                pq.push({ dist[E->to], E->to });
            }
        }
    }
    return {dist, best_edge};
}


vector<lli> kShortestPaths(int source, int dest, int k) {
    auto [distances, best_edge] = dijkstra_best_edge(dest);
    vector<lli> ans;

    priority_queue< pll, vector<pll>, greater<pll> > pq;
    pq.push({distances[source], source}); // {costo, nodo}

    while(k && !pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();

        ans.push_back(dist);
        k--;

        for(int v = u; ; v = best_edge[v]->to){
            for(auto E: adjList[v]) {
                if(E != best_edge[v]) {
                    lli new_dist = dist - distances[v] + E->cost + distances[E->to];
                    pq.push( {new_dist, E->to} );
                }
            }
            if(!best_edge[v]) break;
        }
    }

    return ans;
}



int main () {
	//fastIO();

    int n, m, k; cin>>n>>m>>k;

    adjList.resize(n+1);
    reversedAdjList.resize(n+1);

    for(int i = 0; i < m; i++) {
        int u, v, c; cin>>u>>v>>c;
        addEdge(u, v, c);
    }

    auto ans = kShortestPaths(1, n, k);
    for(auto x: ans) cout << x << " ";
    cout << endl;


	return 0;
}

