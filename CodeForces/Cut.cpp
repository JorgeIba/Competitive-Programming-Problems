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
    //Edge* res;
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
      //  this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector< lli > dis, pos;
vector< bool > visitado;
const lli INF = numeric_limits<int>::max();
lli n, m;

void addEdge(lli u, lli v, lli index, lli capacity)
{
    Edge* uv = new Edge(v, 0, capacity);
    Edge* vu = new Edge(u, 0, capacity);
    uv->res = vu;
    vu->res = uv;
    uv->idx = index;
    vu->idx = -index;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

lli blockingFlow(lli u, lli t, lli minimo)
{
    if(u==t) return minimo;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge* v = adjList[u][i];
        if(v->capacity > v->flow && dis[u] + 1 == dis[v->to])
        {
            lli f = blockingFlow(v->to, t, min(minimo, v->capacity - v->flow));
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
            while(f = blockingFlow(s, t, INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}

void dfs(int id)
{
    if(visitado[id]) return;
    visitado[id] = true;
    for(Edge* v: adjList[id])
    {
        if(v->capacity == v->flow) continue;
        else dfs(v->to);
    }
}

int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    visitado.resize(n+1, false);
    adjList.resize(n+1);
    dis.resize(n+1);
    pos.resize(n+1);
    forn(i,1,m+1)
    {
        lli u, v, c; cin>>u>>v>>c;
        addEdge(u,v,i,c);
    }
    lli maxFlow = dinic(1,n);
    dfs(1);
    set<lli> ans;
    for(int i = 1; i<=n; i++)
    {
        if(!visitado [i] ) continue;
        for(Edge* v: adjList[i])
        {
            if(!visitado[v->to]) ans.insert(abs(v->idx));
        }
    }
    cout<<ans.size()<<" "<<maxFlow<<endl;
    for(auto x: ans)
    {
        cout<<x<<" ";
    }
    cout<<endl;


    return 0;
}