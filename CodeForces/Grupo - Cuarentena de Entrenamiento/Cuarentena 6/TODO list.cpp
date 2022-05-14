#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Edge
{
    lli to, flow, capacity;
    Edge* res;
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector< vector<bool> > rest;
vector<lli> pos;
vector<lli> dist;


void addEdge(lli u, lli v, lli capacity)
{
    Edge* uv = new Edge(v,0,capacity);
    Edge* vu = new Edge(u,0,0);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

const lli INF = 1e18;

lli blockingFlow(lli u, lli t, lli flow)
{
    if(u==t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge* v = adjList[u][i];
        if(v->capacity > v->flow && dist[u] + 1 == dist[v->to])
        {
            lli f = blockingFlow(v->to, t, min(flow, v->capacity  - v->flow));
            if(f>0)
            {
                v->addFlow(f);
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
            for(Edge *v: adjList[u])
            {
                if(dist[v->to]==-1 && v->capacity > v->flow)
                {
                    dist[v->to] = dist[u] + 1;
                    q.push(v->to);
                }
            }
        }
        if(dist[t]!=-1)
        {
            lli f= 0;
            fill(all(pos), 0);
            while(f = blockingFlow(s,t,INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}




int main()
{
    fastIO();
    lli n, m, r; cin>>n>>m>>r;
    adjList.resize(2*(n+2));
    rest.assign(n+2, vector<bool>(n+2));
    pos.resize(2*(n+2));
    dist.resize(2*(n+2));

    vector< pair<lli,lli> > Nodos(n);

    for(auto &x: Nodos)
    {
        cin>>x.first>>x.second;
    }
    for(int i =0; i<r; i++)
    {
        lli u,v; cin>>u>>v;
        rest[u][v] = true;
        rest[v][u] = true;
    }
    forn(i,1,n+1) // 2*i + 1 -> salida, 2*i -> entrada;
    {
        addEdge(1, 2*i+1, 1);
        //addEdge(2*i + 1, 2*i, 1);
        addEdge(2*i, 2*(n+1), 1);
    }

    for(int i = 0; i<n; i++)
    {
        lli ustart = Nodos[i].first, utime = Nodos[i].second;
        for(int j = 0; j<n; j++)
        {
            lli vstart = Nodos[j].first;
            if(i!=j && !rest[i+1][j+1]  && (ustart + utime <= vstart))
            {
                addEdge( 2*(i+1)+1 , 2*(j+1), 1 );
            }
        }
    }

    lli res = dinic(1, 2*(n+1));

    cout<< n-res << endl;

    return 0;
}