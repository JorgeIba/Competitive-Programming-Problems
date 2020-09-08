#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

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

    void addEdge(int u, int v, lli capacity, bool directed = false)
    {
        Edge* uv = new Edge(v, capacity);
        Edge* vu = new Edge(u, directed?0:capacity); // change 0 for capacity if is undirected
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    lli BlockingFlow(int u, int t, lli flow)
    {
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ )
        {
            Edge* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1)
            {
                lli f = BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0)
                {
                     E->addFlow(f); 
                     return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t)
    {
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* E: adjList[u])
            {
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit))
                {
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    lli StartDinic(int s, int t)
    {
        lli maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1) // (1<<30) is for maximum capacity = 10^9
        {
            dist[t] = 0;
            while(bfs(s, t))
            {
                int f = 0;
                fill(all(pos), 0);
                while((f = BlockingFlow(s, t, INF)))
                {
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }
};


int main () {
	fastIO();
    lli n, m; cin>>n>>m;
    Dinic D(n+1, true);
    for(int i = 0; i<m; i++)
    {
        lli u, v, c; cin>>u>>v>>c;
        D.addEdge(u, v, c);
    }

    cout << D.StartDinic(1, n) << endl;
	return 0;
}