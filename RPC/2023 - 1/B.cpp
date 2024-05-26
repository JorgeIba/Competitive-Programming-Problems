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

#define cost first
#define to second

const int MAXN = 1e4+1000;
vector< pair<lli, lli> > adjList[MAXN];
lli costs[MAXN];
const lli INF = 1e17;


typedef pair<lli,lli> pairi;
lli dijkstra(int start, int t, int n){   
    vector<lli> dist( n, INF );

    priority_queue< pairi, vector<pairi>, greater<pairi> > pq;

    pq.push({0,start}); 
    dist[start] = 0;

    while(!pq.empty()){
        auto [dist_u, u] = pq.top(); pq.pop();
        
        if(dist_u > dist[u]) continue;

        for(auto [v, w]: adjList[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist[t];
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int aleatorio(int a, lli b){
	std::uniform_int_distribution<int> dist(a, b);
	return dist(rng);
}


int main () {
	fastIO();
	
    int n, m; cin>>n>>m;
    int s = n, t = n+1;

    for(int i = 0; i < n; i++){
        lli w; cin>>w;
        costs[i] = w;
    }

    for(int i = 0; i < m; i++){
        lli u, v, w; cin>>u>>v>>w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }


    const int ITER = 200;

    lli ans = INF;
    for(int tries = 0; tries < ITER; tries++) {

        vector<int> yes;
        for(int i = 0; i < n; i++) {
            if(aleatorio(0, 1) % 2) {
                yes.push_back(i);
                adjList[i].push_back({t, costs[i]});
            } else {
                adjList[s].push_back({i, costs[i]});
            }
        }
    
        ans = min(ans, dijkstra(s, t, n+2));
    
        adjList[s].clear();
        for(auto i: yes) {
            adjList[i].pop_back();
        }
    }


    assert(ans < INF);
    cout << ans << endl;



	return 0;
}

