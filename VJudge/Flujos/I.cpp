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

template <typename T = int> struct Edge {
    int to;
    T flow, capacity;
    bool rev;
    Edge *res;
    Edge(int to, T capacity, bool rev = false)
        : to(to), flow(0), capacity(capacity), rev(rev) {}
    void addFlow(T flow) {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

// MUCHO OJO CON ESTO
const int INF = 1e9;

template <typename T = int> struct Dinic {
    vector<vector<Edge<T> *>> adjList;
    vector<int> pos, dist;
    int N;
    T limit = 1;
    T maxFlow = 0;
    const bool scaling = false;

    Dinic(int N) : N(N) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, bool directed = true) {
        Edge<T> *uv = new Edge<T>(v, capacity, false);
        Edge<T> *vu = new Edge<T>(u, directed ? 0 : capacity, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    T BlockingFlow(int u, int t, T flow) {
        if (u == t)
            return flow;
        for (int &i = pos[u]; i < (int)adjList[u].size(); i++) {
            Edge<T> *E = adjList[u][i];
            if (E->capacity > E->flow && dist[E->to] == dist[u] + 1) {
                lli f =
                    BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if (f > 0) {
                    E->addFlow(f);
                    return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t) {
        fill(all(dist), -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()) {
            lli u = q.front();
            q.pop();
            for (auto E : adjList[u]) {
                if (dist[E->to] == -1 && E->capacity > E->flow &&
                    (!scaling || E->capacity - E->flow >= limit)) {
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }

    T StartDinic(int s, int t) {
        maxFlow = 0;
        for (limit = (scaling ? 1 << 30 : 1); limit > 0;
             limit >>= 1) { // (1<<30) is for maximum capacity = 10^9
            dist[t] = 0;
            while (bfs(s, t)) {
                lli f = 0;
                fill(all(pos), 0);
                while ((f = BlockingFlow(s, t, INF))) {
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }

    // To found if an edge is part of min-cut
    // Run dfs(S) and if U is part of T and is
    // visited, then is part of min-cut
    vector<bool> visited;
    void dfs(int u, bool clearing = true) {
        if (clearing)
            visited.resize(N);
        if (visited[u])
            return;
        visited[u] = true;
        for (auto E : adjList[u]) {
            if (E->capacity == E->flow)
                continue;
            dfs(E->to, false);
        }
    }
};


int main () {
	//fastIO();
	
    int n, m, s, t; cin>>n>>m>>s>>t;

    Dinic D(n);
    forn(i, m){
        int u, v, w; cin>>u>>v>>w;
        D.addEdge(u, v, w);
    }

    auto ans_cut = D.StartDinic(s, t);

    D.dfs(s);
    vector<int> cut;
    forn(i, n){
        if(D.visited[i]) cut.push_back(i);
    }

    cout << SZ(cut) << endl;
    for(auto x: cut) cout << x << endl;




	return 0;
}

