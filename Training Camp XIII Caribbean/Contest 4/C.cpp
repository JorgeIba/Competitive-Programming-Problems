#include<bits/stdc++.h>

#define lli long long int
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i, a, n) for(int i = (a); i <= (b); i++)
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
#define all(v) v.begin(), v.end()
#define SZ(v) (int)v.size()

using namespace std;


template<typename T = int>
struct Edge{
    int to;
    T flow, capacity, cost;
    bool rev;
    Edge *res;
    Edge(int to, T capacity, T cost, bool rev = false): to(to), flow(0), capacity(capacity), cost(cost), rev(rev) {}

    void addFlow(T flow) {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

const lli INF_FLOW = 1e9, INF_COST = 1e9;
const int INF = 1e9;


template<typename T = int>
struct MinCostFlow{
    vector< vector< Edge<T>* > > adjList;
    vector< int > pos, dist;
    int N;

    MinCostFlow(int N): N(N) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, T cost){
        Edge<T>* uv = new Edge<T>(v, capacity, cost);
        Edge<T>* vu = new Edge<T>(u, 0, -cost, true);
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
                if(dist[E->to] == -1 && E->capacity > E->flow){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    T StartDinic(int s, int t){
        int maxFlow = 0;
        dist[t] = 0;
        while(bfs(s, t)){
            lli f = 0;
            fill(all(pos), 0);
            while((f = BlockingFlow(s, t, INF))){
                maxFlow += f;
            }
        }
        return maxFlow;
    }


    pair<T, T> getMinCostFlow(int s, int t, int limit) {
        vector<T> dist(N), cap(N);
        vector<bool> inQueue(N);
        vector< Edge<T>* > parent(N);

        T minCost = 0, maxFlow = 0;

        while(true){
            fill(all(dist), INF_COST);
            fill(all(cap), 0);
            fill(all(parent), nullptr);

            queue<int> q;
            q.push(s);
            dist[s] = 0;
            cap[s] = INF_FLOW;

            while(!q.empty()) {
                int u = q.front(); q.pop();
                inQueue[u] = 0;

                for(auto E: adjList[u]){
                    int v = E->to;
                    if(E->flow < E->capacity && dist[u] + E->cost < dist[v]) {
                        
                        dist[v] = dist[u] + E->cost;

                        cap[v] = min(cap[u], E->capacity - E->flow);

                        parent[v] = E;

                        if(!inQueue[v]) {
                            inQueue[v] = 1;
                            q.push(v);
                        }

                    }
                }
            }

            if(!parent[t]) break;
            
            if(limit < dist[t]) break;

            assert(cap[t] > 0);
            cap[t] = 1;
            limit -= dist[t];


            maxFlow += cap[t];
            minCost += cap[t] * dist[t];

            for(int u = t; u != s; u = parent[u]->res->to) {
                parent[u]->addFlow(cap[t]);
            }
        }

        return {minCost, maxFlow};
    }
};




int main(){
	// fastIO();

    int n, k; cin>>n>>k;

    MinCostFlow<int> *D = new MinCostFlow<int>(n);
    vector< vector<int> > cap(n, vector<int>(n));


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin>>cap[i][j];
            if(i != n-1 && cap[i][j]) {
                D->addEdge(i, j, cap[i][j], 0);                
            }
        }
    }

    int s = 0, t = n-1;

    auto flow = D->StartDinic(s, t);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(cap[i][j]){
                D->addEdge(i, j, k, 1);
            }
        }
    }

    
    flow += D->getMinCostFlow(s, t, k).second;
    cout << flow << endl;

	return 0;
}