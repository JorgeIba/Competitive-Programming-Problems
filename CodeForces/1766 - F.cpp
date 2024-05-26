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

    void addEdge(int u, int v, T capacity, T cost, int idx){
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
            // if(dist[t] > 0) break;

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

    int n, m; cin>>n>>m;

    MinCostFlow<lli> *MCF = new MinCostFlow<lli>(n+2);

    int s = 0, t = n-1;
    int s_prime = n, t_prime = n+1;

    vector<int> lowers(m);
    vector<int> dem(n);
    int total_cost_units = 0;
    for(int i = 0; i < m; i++) {
        int u, v, c, w; cin>>u>>v>>c>>w;
        u--, v--;

        if(c & 1) {
            lowers[i]++;

            total_cost_units += w;

            dem[u] += 1;
            dem[v] -= 1;

            MCF->addEdge(u, v, (c-1) / 2, 2*w, i);
        } else {
            MCF->addEdge(u, v, c / 2, 2*w, i);
        }        
    }

    bool impossible = false;
    if(dem[s] % 2 || dem[t] % 2) {
        if(dem[s] % 2 && dem[t] % 2) {
            MCF->addEdge(s, t, 1, 0, m+1);
        } else {
            impossible = true;
        }
    }

    lli offset = 0;
    for(int u = 1; u < n-1; u++){
        if(dem[u] & 1){
            impossible = true;
        }
        
        if(dem[u] < 0) {
            MCF->addEdge(s_prime, u, -dem[u] / 2, -INF_COST,  m+1);
            offset += INF_COST;

        } else if(dem[u] > 0) {
            MCF->addEdge(u, t_prime,  dem[u] / 2, -INF_COST,  m+1);
            offset += INF_COST;
        }
    }

    MCF->addEdge(s_prime, s, INF_FLOW, 0, m+1);
    MCF->addEdge(t, t_prime, INF_FLOW, 0, m+1);
    
    auto [cost, flow] = MCF->getMinCostFlow(s_prime, t_prime);

    lli ans = cost + offset + total_cost_units;

    cerr << ans << " " << flow << endl;

    vector<int> ans_flows(m);
    for(int i = 0; i < n+2; i++) {
        for(auto v: MCF->adjList[i]) {
            if(v->rev) continue;
            if(v->cost == -INF_COST) {
                if(v->flow != v->capacity){
                    impossible = true;
                }
            }
            if(v->idx < m) {
                ans_flows[v->idx] = 2*v->flow + lowers[v->idx];
            }
        }
    }

    if(impossible){
        cout << "Impossible" << endl;
    } else {
        cout << "Possible" << endl;
        for(auto x: ans_flows) cout << x << " ";
        cout << endl;
    }


	return 0;
}

