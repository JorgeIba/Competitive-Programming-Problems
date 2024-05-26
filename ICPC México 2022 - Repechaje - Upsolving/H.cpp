#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

typedef pair<int,int> pairr;


struct Edge{
    lli to, flow, capacity;
    Edge* res;
    Edge(int to, lli capacity, lli cost = 0): to(to), flow(0), capacity(capacity) {}
    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

struct Dinic{
    vector< vector< Edge* > > adjList;
    vector< int > pos, dist;
    lli N;
    lli limit = 1;
    bool scaling;
    const lli INF = numeric_limits<lli>::max();

    Dinic(lli N, bool withScaling = false): N(N), scaling(withScaling) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, lli capacity, bool directed = false){
        Edge* uv = new Edge(v, capacity);
        Edge* vu = new Edge(u, directed?0:capacity); // change 0 for capacity if is undirected
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    lli BlockingFlow(int u, int t, lli flow){
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ ){
            Edge* E = adjList[u][i];
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
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty()){
            lli u = q.front(); q.pop();
            for(Edge* E: adjList[u]){
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit)){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    lli StartDinic(int s, int t){
        lli maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1) // (1<<30) is for maximum capacity = 10^9
        {
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
};


int main () {
	//fastIO();
    int n, m; cin>>n>>m;
    
    vector< vector< int > > adjList(n);
    vector< pairr > undirected;
    vector< int > in(n), out(n), poss(n);
    for(int i = 0; i < m; i++){
        int u, v, t; cin>>u>>v>>t; u--, v--;
        if(t == 0){
            undirected.push_back({u, v});
            poss[u]++;
            poss[v]++;
        }else{
            adjList[u].push_back(v);
            in[v]++;
            out[u]++;
        }
    }

    Dinic *D = new Dinic(n + SZ(undirected) + 2);
    int s = n + SZ(undirected);
    int t = n + SZ(undirected) + 1;

    bool ans = true;
    for(int i = 0; i < n; i++){
        int total = in[i] + out[i] + poss[i];
        if(total % 2)
            ans = false;

        int need = total / 2 - out[i];

        if(need > poss[i] || need < 0)
            ans = false;        

        D->addEdge(i, t, need, true);
    }

    if(!ans) {
        cout << "NO" << endl;
        return 0;
    }


    for(int i = 0; i < SZ(undirected); i++) {
        auto edge = undirected[i];
        D->addEdge(s, n + i, 1, 1);
        D->addEdge(n + i, edge.first, 1, 1);
        D->addEdge(n + i, edge.second, 1, 1);
    }


    lli flow = D->StartDinic(s, t);

    if(flow == SZ(undirected)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }


	return 0;
}

