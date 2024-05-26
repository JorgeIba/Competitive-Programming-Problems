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

typedef pair<lli,lli> pairi;

vector< vector< pairi > > adjList;

const lli INF = 1e17;
vector<int> dijkstra(int start, int to){   
    int n = SZ(adjList);
    vector<lli> dist( n, INF );
    vector<int> parent(n);

    priority_queue< pairi, vector<pairi>, greater<pairi> > pq;

    pq.push({0,start}); // {costo, nodo}
    dist[start] = 0;

    while(!pq.empty()){
        auto [dist_u, u] = pq.top(); pq.pop();
        
        if(dist_u > dist[u]) continue;

        for(auto [v, w]: adjList[u]){
            if(dist[u] + w < dist[v]){
                parent[v] = u;
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }

    if(dist[to] == INF) {
        return {};
    }

    vector<int> ans;
    int curr = to;
    while(curr != start){
        ans.push_back(curr);
        curr = parent[curr];
    }

    ans.push_back(start);
    reverse(all(ans));

    return ans;
}




int main () {
	fastIO();
	
    int n, m; cin>>n>>m;

    adjList.resize(n+1);
    forn(i, m){
        int u, v, w; cin>>u>>v>>w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    auto ans = dijkstra(1, n);

    if(ans.empty()) {
        cout << -1 << endl;
    } else {
        for(auto x: ans) cout << x << " ";
        cout << endl;
    }

    

	return 0;
}

