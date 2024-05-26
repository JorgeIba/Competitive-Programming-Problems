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


template<typename T = int>
struct Edge{
    int to;
    T flow, capacity, cost;
    int idx;
    bool rev;
    Edge* res;
    Edge(int to, T capacity, T cost, int idx, bool rev = false): to(to), flow(0), capacity(capacity), cost(cost), idx(idx), rev(rev) {}
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

//MUCHO OJO CON ESTO
const lli INF_FLOW = 1e15, INF_COST = 1e9;

template<typename T = int>
struct MinCostFlow{
    vector< vector< Edge<T>* > > adjList;
    int N;

    MinCostFlow(int N): N(N){
        adjList.resize(N);
    }

    void addEdge(int u, int v, T capacity, T cost, int idx=1){
        Edge<T>* uv = new Edge<T>(v, capacity, cost, idx);
        Edge<T>* vu = new Edge<T>(u, 0, -cost, idx, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    pair<T, T> getMinCostFlow(int s, int t) {
        vector<T> dist(N), cap(N);
        vector<bool> inQueue(N);
        vector< Edge<T>* > parent(N);  

        T minCost = 0, maxFlow = 0;

        while(true) {

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

                for(auto E: adjList[u]) {
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
            if(dist[t] > 0) break;

            maxFlow += cap[t];
            minCost += cap[t] * dist[t];
            
            for(int u = t; u != s; u = parent[u]->res->to){
                parent[u]->addFlow(cap[t]);
            }
        }
        return {minCost, maxFlow};
    }
};


int main () {
	//fastIO();

    int n, k; cin>>n>>k;
    n++;

    int s = 2*n + 1, t = s+1;
    MinCostFlow<lli> MCF(t+1);

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            int k; cin>>k;
            if(i == 0){
                MCF.addEdge(i, 2*j, INF_FLOW, k);
            } else {
                MCF.addEdge(2*i+1, 2*j, INF_FLOW, k);
            }
        }
    }

    for(int i = 1; i < n; i++){
        MCF.addEdge(2*i, 2*i+1, 1, -INF_COST);
        MCF.addEdge(2*i+1, t, 1, 0);
    }

    MCF.addEdge(s, 0, k, 0);

    auto [cost, flow] = MCF.getMinCostFlow(s, t);
    cout << cost + (n-1)*INF_COST << endl;
	


	return 0;
}

