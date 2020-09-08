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

vector< vector< Edge* > > adjList;
vector<lli> dis;
vector<lli> pos;
const lli INF = numeric_limits<lli>::max();
lli n, m;

void addEdge1(lli u, lli v, lli capacity)
{
    Edge* uv = new Edge(v, 0, capacity);
    Edge* vu = new Edge(u, 0, capacity);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

void addEdge2(lli u, lli v, lli capacity)
{
    Edge* uv = new Edge(v, 0, capacity);
    Edge* vu = new Edge(u, 0, 0);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

lli blockingFlow(lli u, lli t, lli minimo)
{
    if(u==t) return minimo;
    for(lli &i= pos[u]; i<adjList[u].size(); i++)
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
    fill(all(dis), -1);
    dis[t] = 0;
    while(dis[t]!=-1)
    {
        fill(all(dis), -1);
        queue<lli> Q;
        Q.push(s);
        dis[s] = 0;
        while(!Q.empty())
        {
            lli u = Q.front(); Q.pop();
            for(Edge* v: adjList[u])
            {
                if(dis[v->to] == -1 && v->capacity > v->flow)
                {
                    dis[v->to] = dis[u] + 1;
                    Q.push(v->to);
                }
            }
        }
        if(dis[t]!=-1)
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





int main() //par->entrada, impar->salida
{
    fastIO();
    cin>>n>>m;
    adjList.resize(2*n + 100);
    dis.resize(2*n + 100);
    pos.resize(2*n + 100);
    for(int i = 0; i<n-1; i++)
    {
        lli c; cin>>c;
        addEdge2(2*i, 2*i+1, c);
    }
    for(int i = 0; i<m; i++)
    {
        lli u, v, c; cin>>u>>v>>c;
        u--, v--;
        addEdge1(2*u + 1, 2*v ,c);
    }


    cout<<dinic(0, 2*(n-1))<<endl;


    return 0;
}