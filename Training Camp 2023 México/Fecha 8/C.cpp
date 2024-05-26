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
const lli INF_FLOW = 1e9, INF_COST = 1e9;

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


void main_(){
    int n, m; cin>>n>>m;

    int s = 2*n, t = 2*n+1;
    MinCostFlow<lli> *MCF = new MinCostFlow<lli>(2*n+2);

    vector< vector<int> > adjList(n);
    vector< int > in(n), out(n);
    lli offset = 0;
    forr(i, 1, m){
        int u, v, d; cin>>u>>v>>d;
        u--, v--;
        adjList[u].push_back(v);

        out[u]++;
        in[v]++;

        MCF->addEdge(u, v, INF_FLOW, d, 1);
        offset += d;
    }

    auto bfs = [&](int s) {
        vector<bool> visited(n);
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            auto u = q.front(); 
            q.pop();
            visited[u] = true;
            for(auto v: adjList[u]) {
                if(visited[v]) continue;
                q.push(v);
            }
        }
        for(auto x: visited)
            if(!x) return false;
        return true;
    };


    bool impossible = false;
    forn(i, n) {
        if(!bfs(i)) 
            impossible = true;
    }

    lli flow_entry = 0, flow_out = 0;
    for(int i = 0; i < n; i++){
        if(in[i] < out[i]) {
            flow_entry += out[i] - in[i];
            MCF->addEdge(i, t, out[i] - in[i], 0, 1);    
        } else if(out[i] < in[i]) {
            flow_out += in[i] - out[i];
            MCF->addEdge(s, i, in[i] - out[i], 0, 1);
        }
    }

    if(flow_entry != flow_out) 
        impossible = true;

    if(impossible){
        cout << -1 << endl;
        return;
    }    

    auto [cost, flow] = MCF->getMinCostFlow(s, t);

    if(flow < flow_entry) {
        cout << -1 << endl;
    } else {
        assert(flow == flow_entry);
        cout << cost + offset << endl;
    }    
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

