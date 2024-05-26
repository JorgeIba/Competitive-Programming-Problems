#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


vector< vector< pair<lli,int> > > adjList;
vector< set<lli> > times_wait;

const lli INF = 1e18;

vector<lli> dijkstra(int start) {
    int n = SZ(adjList);
    vector<lli> time_to_move(n, INF);
    vector<lli> shortest_dist(n, INF);

    priority_queue< pair<lli, int> , vector<pair<lli,int>>, greater<pair<lli,int>> > pq;

    pq.push({0, start});
    shortest_dist[start] = 0;
    time_to_move[start] = 0;


    while(!pq.empty()) {
        auto [dist_u, u] = pq.top(); pq.pop();

        if(dist_u < time_to_move[u]) continue;

        if(times_wait[u].count(dist_u)) {
            time_to_move[u] = dist_u+1;
            pq.push({dist_u+1, u});
            continue;
        }

        for(auto [v, cost]: adjList[u]) {
            if(time_to_move[u] + cost < shortest_dist[v]) {
                shortest_dist[v] = time_to_move[u] + cost;
                time_to_move[v] = shortest_dist[v];
                pq.push({shortest_dist[v], v});
            }
        }
    }

    return shortest_dist;
}

int main () {
	//fastIO();

    int n, m; cin>>n>>m;
    adjList.resize(n);
    times_wait.resize(n);

    for(int i = 0; i < m; i++){
        int u, v, c; cin>>u>>v>>c; u--, v--;
        adjList[u].push_back({v, c});
        adjList[v].push_back({u, c});
    }

    for(int i = 0; i < n; i++) {
        int k; cin>>k;
        for(int j = 0; j < k; j++){
            int t; cin>>t;
            times_wait[i].insert(t);
        }
    }

    auto ans = dijkstra(0)[n-1];

    cout << (ans != INF ? ans : -1 ) << endl;


	return 0;
}

