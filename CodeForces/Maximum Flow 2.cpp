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
    lli to, flow, capacity, idx;
    Edge* res;
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;

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

lli n, m;
lli EdmondKarps(lli s, lli t)
{
    lli maximumFlow = 0;
    vector< Edge* > parent(n+1);
    while(true)
    {
        fill(all(parent), nullptr);
        queue<lli> Q;
        Q.push(s);
        while(!Q.empty())
        {
            lli u = Q.front(); Q.pop();
            for(Edge* v: adjList[u])
            {
                if(!parent[v->to] && v->capacity > v->flow)
                {
                    parent[v->to] = v;
                    Q.push(v->to);
                }
            }
        }
        if(!parent[t]) break;
        lli f = INF;
        for(lli u = t; u!=s; u = parent[u]->res->to)
            f = min(f, parent[u]->capacity - parent[u]->flow);
        for(lli u = t; u!=s; u= parent[u]->res->to)
            parent[u]->addFlow(f);
        maximumFlow+=f;
    }
    return maximumFlow;
}

int main()
{
    fastIO();
    cin>>n>>m;
    adjList.resize(n+1);
    vector<lli> res(m+1);
    forn(i,1,m+1)
    {
        lli u, v, c; cin>>u>>v>>c;
        addEdge(u, v, i, c);
    }
    cout<<EdmondKarps(1,n)<<endl;
    for(int i = 1; i<=n; i++)
    {
        for(Edge* v: adjList[i])
        {
            lli idx = v->idx;
            lli flow = v->flow;
            if(idx < 0)
            {
                flow -= flow;
                idx -= idx;
            }
            res[idx] = flow;
        }
    }
    for(int i = 1; i<=m; i++)
    {
        cout<<res[i]<<endl;
    }


    return 0;
}