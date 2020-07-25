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
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {};
    
    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector<lli> pos;
vector<lli> dist;
const lli INF = numeric_limits<lli>::max();

void addEdge(lli u, lli v, lli capacity, bool bi)
{
    Edge* uv = new Edge(v, 0, capacity);
    Edge* vu = new Edge(u, 0, (bi?capacity:0) );
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

lli blockingFlow(lli u, lli t, lli flow)
{
    if(u==t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge* v = adjList[u][i];
        if(v->capacity > v->flow && dist[u]+1==dist[v->to])
        {
            lli f = blockingFlow(v->to, t, min(flow, v->capacity - v->flow));
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
    while(dist[t]!=-1)
    {
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* v: adjList[u])
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
            lli f = 0;
            fill(all(pos), 0);
            while(f = blockingFlow(s,t,INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}



void solve(lli n, lli m)
{
    adjList.clear(); adjList.resize(n+2);
    pos.clear(); pos.resize(n+2);
    dist.clear(); dist.resize(n+2);

    for(int i = 1; i<=n; i++)
    {
        lli des; cin>>des;
        if(des)
        {
            addEdge(0, i, 1, false);
        } 
        else 
        {
            addEdge(i, n+1, 1, false);
        }   
    }
    forn(i,0,m)
    {
        lli u,v; cin>>u>>v;
        u,v;
        addEdge(u,v,1,true);
    }

    cout<<dinic(0,n+1)<<endl;
    

}



int main()
{
    fastIO();
    lli n, m;
    while(true)
    {
        cin>>n>>m;
        if(n==0 && m==0) return 0;
        solve(n,m);
    }
    return 0;
}