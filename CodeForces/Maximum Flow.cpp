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
    lli to, flow, capacity, idx;
    Edge* rev;
    Edge(lli to, lli flow, lli capacity, Edge* rev = NULL): to(to), capacity(capacity), flow(flow), rev(rev){}

    void addFlow(lli flow)
    {
        this->flow += flow;
        //this->rev->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector< lli > dist;
vector< lli > pos;
lli inf = numeric_limits<int>::max();
vector< lli > res;


void addEdge(int u, int v, int idx, lli capacity)
{
    Edge *uv = new Edge(v, 0, capacity);
    Edge *vu = new Edge(u, 0, capacity);
    //uv->rev = vu;
    //vu->rev = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
    uv->idx = idx;
    vu->idx = -idx;
}

lli blockingFlow(lli u, lli t, lli flow)
{
    if(u==t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); ++i)
    {
        Edge* v = adjList[u][i];
        if(v->capacity > v->flow && dist[u] == dist[v->to] - 1)
        {
            lli fv = blockingFlow(v->to, t, min(flow, v->capacity - v->flow));
            if(fv > 0)
            {
                //cout<<u<<" "<<v->to<<" "<<fv<<endl;
                v->addFlow(fv);
                return fv;
            }
        }
    }
    return 0;
}



lli dinic(int s, int t)
{
    lli maxFlow = 0;
    dist[t] = 0;
    while(dist[t] != -1)
    {
        fill(dist.begin(), dist.end(), -1);
        queue<lli> q;
        q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front();
            q.pop();
            for(Edge* v: adjList[u])
            {
                if(dist[v->to] == -1 && v->capacity != v->flow)
                {
                    dist[v->to] = dist[u] + 1;
                    q.push(v->to);
                }
            }
        }

        if(dist[t] != -1)
        {
            lli aux = 0;
            fill(pos.begin(), pos.end(), 0);
            while(aux = blockingFlow(s, t, inf))
            {
                maxFlow += aux;
            }
        }

    }
    return maxFlow;
}



int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    adjList.resize(n+1);
    pos.resize(n+1);
    dist.resize(n+1);
    res.resize(m+1);
    for(int i = 1; i<=m; i++)
    {
        lli u, v, c; cin>>u>>v>>c;
        addEdge(u,v,i,c);
    }
    cout<<dinic(1,n)<<endl;
    
    for(int i = 1; i<= n; i++)
    {
        for(Edge* v: adjList[i])
        {
            lli idx = v->idx;
            lli flow = v->flow;
            if(idx < 0)
            {
                idx = -idx;
                flow = -flow;
            }
            flow != 0? res[idx] = flow: res[idx];
            //cout<<idx<<" "<<res[idx]<<endl;
        }
    }

    for(int i = 1; i<=m; i++)
    {
        cout<<res[i]<<endl;
    }


    return 0;
}