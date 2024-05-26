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


template<typename T = int>
struct Edge{
    int to;
    T flow, capacity;
    bool rev;
    Edge* res;
    Edge(int to, T capacity, bool rev = false): to(to), flow(0), capacity(capacity), rev(rev) {}
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

const int INF = 1e9;

template<typename T = int>
struct Dinic{
    vector< vector< Edge<T>* > > adjList;
    vector< int > pos, dist;
    int N;
    T limit = 1;
    T maxFlow = 0;
    bool scaling = false;


    Dinic(int N): N(N){
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, bool directed = true){
        Edge<T>* uv = new Edge<T>(v, capacity, false);
        Edge<T>* vu = new Edge<T>(u, directed?0:capacity, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    T BlockingFlow(int u, int t, T flow){
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ ){
            Edge<T>* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1){
                lli f = BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0){
                    E->addFlow(f);
                    return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t){
        fill(all(dist), -1);
        queue<int> q; q.push(s);
        dist[s] = 0;
        while(!q.empty()){
            lli u = q.front(); q.pop();
            for(auto E: adjList[u]){
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit)){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }

    void resetFlow() {
        for(int i = 0; i < SZ(adjList); i++){
            for(auto &v: adjList[i]){
                v->flow = 0;
            }
        }
    }
    
    T StartDinic(int s, int t){
        maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1){ 
            dist[t] = 0;
            while(bfs(s, t)){
                lli f = 0;
                fill(all(pos), 0);
                while((f = BlockingFlow(s, t, INF))){
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }

    //To found if a edge is part of min-cut
    //Run dfs(S) and if U is part of T and is
    //visited, then is part of min-cut
    vector<bool> visited;
    void dfs(int u, bool clearing = true) {
        if(clearing) visited.resize(N);
        if(visited[u]) return;
        visited[u] = true;
        for(auto E: adjList[u]){
            if(E->capacity == E->flow) continue;
            dfs(E->to, false);
        }
    }
};



int main () {
	fastIO();
	
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);


    int n, m, a, b; cin>>n>>m>>a>>b;

    Dinic<int> *D = new Dinic<int>(n+1);

    D->scaling = true;

    for(int i = 0; i < m; i++) {
        int u, v, c; cin>>u>>v>>c;
        D->addEdge(u, v, c, false);
    }

    auto cost_init = D->StartDinic(a, b);

    D->dfs(a);

    vector< Edge<int>* > cuts;
    for(int i = 1; i <= n; i++) {
        if(!D->visited[i]) continue;
        for(auto E: D->adjList[i]) {
            if( !D->visited[E->to] ) {
                cuts.push_back(E);
            }
        }
    }

    // cout << "Cut: " << endl;
    // for(auto E: cuts) {
    //     cout << E->to << " -> " << E->flow << "/" << E->capacity << endl;
    // } 

    // cout << D->bfs(a, b) << endl;

    // cuts[1]->capacity++;

    // cout << D->bfs(a, b) << endl;

    D->scaling = false;

    auto unique = true;
    for(auto E: cuts) {
        E->capacity++;

        if(!D->bfs(a, b))
            unique = false;

        E->capacity--;
    }


    cout << (unique ? "UNIQUE" : "AMBIGUOUS") << endl;



	return 0;
}

