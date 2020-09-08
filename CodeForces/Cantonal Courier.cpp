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
    lli to, cost, flow, capacity;
    Edge* res;
    Edge(lli to, lli capacity, lli cost = 0): to(to), cost(cost), flow(0), capacity(capacity) {}
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
    const lli INF = numeric_limits<lli>::max();

    Dinic(lli N): N(N){
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(lli u, lli v, lli capacity)
    {
        Edge* uv = new Edge(v, capacity);
        Edge* vu = new Edge(u, 0);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    lli blockingFlow(lli u, lli t, lli flow)
    {
        if(u == t) return flow;
        for(int &i= pos[u]; i<adjList[u].size(); i++ )
        {
            Edge* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1)
            {
                lli f = blockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0)
                {
                     E->addFlow(f); 
                     return f;
                }
            }
        }
        return 0;
    }

    lli dinic(lli s, lli t)
    {
        lli maxFlow = 0;
        dist[t] = 0;
        while(dist[t] != -1)
        {
            fill(all(dist), -1);
            queue<lli> q; q.push(s);
            dist[s] = 0;
            while(!q.empty())
            {
                lli u = q.front(); q.pop();
                for(Edge* E: adjList[u])
                {
                    if(dist[E->to] == -1 && E->capacity > E->flow)
                    {
                        dist[E->to] = dist[u] + 1;
                        q.push(E->to);
                    }
                }
            }
            if(dist[t] != -1)
            {
                lli f = 0;
                fill(all(pos), 0);
                while((f = blockingFlow(s, t, INF)))
                {
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
        
    }
};

const lli maxN = 105;
lli cost[maxN];
lli profit[maxN];

int main () {
	fastIO();
    lli n, m; cin>>n>>m;
    Dinic D(n+m+2);
    //1 a m, trabajos
    //m+1 a m + n costos
    //s = 0, t = m+n+1
    lli s = 0, t = m+n+1;
    for(int i = 1; i<=n; i++)
    {
        cin>>cost[i];
        D.addEdge(m+i, t, cost[i]);
    }
    lli ans = 0;
    for(int i = 1; i<=m; i++){
        cin>>profit[i]; ans+= profit[i];
        D.addEdge(s, i, profit[i]);
    }
    for(int i = 1; i<=m; i++)
    {
        lli tickets; cin>>tickets;
        for(int j = 0; j<tickets; j++)
        {
            lli city; cin>>city;
            D.addEdge(i, m + city, 1e18);
        }
    }
    
    ans -= D.dinic(s, t);
    lli total = 0;
    for(Edge* E: D.adjList[0])
    {
        total += E->capacity - E->flow;
    }
    //cout << total << endl;
    cout << ans << endl;
    assert(ans == total);



	return 0;
}