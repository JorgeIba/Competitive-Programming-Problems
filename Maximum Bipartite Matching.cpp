#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = numeric_limits<int>::max();

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
vector<lli> dis;
vector<lli> pos;

void addEdge(lli u, lli v, lli capacity)
{
    Edge* uv = new Edge(v, 0, capacity);
    Edge* vu = new Edge(u, 0, 0);
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
        if(v->capacity > v->flow && dis[u] + 1 == dis[v->to])
        {
            lli fv = blockingFlow(v->to, t, min(flow, v->capacity - v->flow));
            if(fv>0)
            {
                v->addFlow(fv);
                return fv;
            }
        }
    }
    return 0;
}




lli dinic(lli s, lli t)
{
    lli maxFlow = 0;
    dis[t] = 0;
    while(dis[t] != -1)
    {
        fill(all(dis), -1);
        queue<lli> q;
        q.push(s);
        dis[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* v: adjList[u])
            {
                if(dis[v->to] == -1 && v->capacity > v->flow)
                {
                    dis[v->to] = dis[u] + 1;
                    q.push(v->to);
                }
            }
        }
        if(dis[t] != -1)
        {
            lli f = 0;
            fill(all(pos), 0);
            while( f = blockingFlow(s,t,INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}




void solve()
{
    lli m, n; cin>>m>>n;
    adjList.clear();
    adjList.resize(n+m+2);
    dis.clear();
    dis.resize(n+m+2);
    pos.clear();
    pos.resize(n+m+2);

    for(int i = 1; i<=m; i++)
    {
        for(int j = 1; j<=n; j++)
        {
            lli a; cin>>a;
            if(a)
            {
                addEdge(j, i+n , 1);
            }
        }
    }
    for(int i = 1; i<=n; i++)
    {
        addEdge(0, i, 1);
    }
    for(int i = 1; i<=m; i++)
    {
        addEdge(i+n, 1+n+m, 1);
    }
    cout<<dinic(0, 1+n+m)<<endl;
}




int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}



