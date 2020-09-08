#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Edge
{
    lli v, flow, c;
    Edge* res;

    Edge(): v(0), flow(0) {}
    Edge(lli v, lli c): v(v), flow(0), c(c) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector< Edge* > > adjList;
vector< lli > pos, dist;
lli total = 0;
const lli INF = 1e18;
lli n, m;



void addEdge(lli u, lli v, lli c)
{
    Edge *uv = new Edge(v, 1);
    Edge *vu = new Edge(u, 0);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}


lli blocking(lli u, lli t, lli flow)
{
    if(u == t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge *E = adjList[u][i];
        if( E->flow < E->c && dist[E->v] == dist[u] + 1 )
        {
            lli f = blocking(E->v, t, min(flow, E->c - E->flow));
            if(f > 0)
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
            for(Edge *E: adjList[u])
            {
                if(dist[E->v] == -1 && E->flow < E->c)
                {
                    dist[E->v] = dist[u] + 1;
                    q.push(E->v);
                }
            }
        }

        if(dist[t] != -1)
        {
            lli f = 0;
            fill(all(pos), 0);
            while(f = blocking(s, t, INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}

void prep(lli n)
{
    adjList.clear(); adjList.resize(n);
    dist.clear(); dist.resize(n);
    pos.clear(); pos.resize(n);
}


void solve()
{
    prep(2*(n+2));

    for(int i = 0; i<m; i++) // 2*i -> entrada, 2*i + 1 -> salida
    {
        lli u, v; cin>>u>>v;
        addEdge(2*v+1,2*u,1);
    }
    lli S = 2*n, T = 2*(n+1);
    
    for(int i = 0; i<n; i++)
    {
        addEdge(S+1, 2*i+1, 1);
        addEdge(2*i, T, 1);
    }

    lli flow = dinic(S+1, T);


    //cout << flow << endl;
    if(flow == n) cout << "YES\n";
    else cout << "NO\n";


    return;
}

int main()
{
    while(cin>>n>>m)
    {
        solve();
    }
}