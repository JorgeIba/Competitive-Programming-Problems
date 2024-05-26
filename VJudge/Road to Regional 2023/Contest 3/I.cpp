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

vector<int> adjList[MAXN];
vector<int> adjList_T[MAXN];


bool iron[MAXN], coal[MAXN];

// const int NONE = 0, IRON = 1, COAL = 2, BOTH = 3;

// typedef tuple<int,int,int> state;
const int INF = 1e8;

// int dijkstra(int n, int start){

//     vector< array<int,4> > dist(n+1, {INF, INF, INF, INF});
//     priority_queue<state, vector<state>, greater<state>> pq;
    
//     dist[start][NONE] = 0;
//     pq.push({0, NONE, start});

//     while(!pq.empty()){
//         auto [dist_u, type_d, u] = pq.top(); pq.pop();
//         if(dist_u > dist[u][type_d]) continue;

//         for(auto v: adjList[u]){
//             int new_type = 0;
//             if(type_d == NONE){

//                 if(iron[v]) new_type = IRON;
//                 else if(coal[v]) new_type = COAL;
//                 else new_type = NONE;

//             } else if(type_d == IRON){

//                 if(iron[v]) new_type = IRON;
//                 else if(coal[v]) new_type = BOTH;
//                 else new_type = IRON;

//             } else if(type_d == COAL) {

//                 if(iron[v]) new_type = BOTH;
//                 else if(coal[v]) new_type = COAL;
//                 else new_type = COAL;

//             } else if(type_d == BOTH) {
//                 new_type = BOTH;
//             }

//             if(dist_u + 1 < dist[v][new_type]){
//                 dist[v][new_type] = dist_u + 1;
//                 pq.push({dist[v][new_type], new_type, v});
//             }
//         }
//     }


//     int ans = INF;
//     forn(i, n){
//         if(dist[i][BOTH] != INF) {
//             ans = min(ans, dist[i][BOTH]);
//         }
//     }
//     return ans;
// }


int main () {
	//fastIO();
	
    int n, m, k; cin>>n>>m>>k;

    vector<int> irons;
    forn(i, m) {
        int x; cin>>x; x--;
        iron[x] = true;
        irons.push_back(x);
    }

    vector<int> coals;
    forn(i, k) {
        int x; cin>>x; x--;
        coal[x] = true;
        coals.push_back(x);
    }

    forn(i, n){
        int l; cin>>l;
        forn(j, l){
            int x; cin>>x; x--;
            adjList[i].push_back(x);
            adjList_T[x].push_back(i);
        }
    }

    auto bfs = [&](vector<int> start, bool rev) {
        vector<int> dist(n, INF);
        queue<int> q;
        for(auto u: start) {
            dist[u] = 0;
            q.push(u);
        }

        while(!q.empty()){
            auto u = q.front(); q.pop();

            if(rev){
                for(auto v: adjList_T[u]){
                    if(dist[v] != INF) continue;

                    dist[v] = dist[u]+1;
                    q.push(v);
                }
            } else {
                for(auto v: adjList[u]){
                    if(dist[v] != INF) continue;

                    dist[v] = dist[u]+1;
                    q.push(v);
                }
            }
            
        }
        return dist;
    };


    auto dist_root = bfs({0}, false);
    auto dist_to_iron = bfs(irons, true);
    auto dist_to_coal = bfs(coals, true);


    int ans = INF;
    for(int i = 0; i < n; i++){
        int dist_i = dist_root[i]; // Llego
        dist_i += dist_to_iron[i]; // Lo mando a un iron
        dist_i += dist_to_coal[i]; // Lo mando a un coal

        ans = min(ans, dist_i);
    }

    if(ans == INF) cout << "impossible" << endl;
    else cout << ans << endl;


	return 0;
}

