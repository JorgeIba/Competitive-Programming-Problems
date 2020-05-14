#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define x first
#define y second
#define punto pair<lli,lli>

using namespace std;

struct Edge{
    lli flow, capacity, to;
    Edge *res;
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {}
    
    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> >  adjList;
vector< lli >  dist;
vector< lli >  pos;
const lli INF = numeric_limits<int>::max();
lli n; 

void addEdge(lli u, lli v, lli capacity)
{
    Edge *uv = new Edge(v, 0, capacity);
    Edge *vu = new Edge(u, 0, 0);
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
        Edge *v = adjList[u][i];
        if(v->capacity > v->flow && dist[u] + 1 == dist[v->to])
        {
            lli f = blockingFlow(v->to, t, min(flow, v->capacity - v->flow));
            if(f > 0)
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
                if(dist[v->to] == -1 && v->capacity > v->flow)
                {
                    dist[v->to] = dist[u] + 1;
                    q.push(v->to);
                }
            }
        }
        if(dist[t] != -1)
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

int main()
{
    fastIO();
    cin>>n;
    adjList.resize(2*n + 2);
    pos.resize(2*n + 2);
    dist.resize(2*n + 2);
    vector<punto> red(n+1);
    vector<punto> blue(n+1);
    // 2*(n) -> inicio, 2*(n+1) -> fin  
    //inicio  -> red -> blue -> fin
    forn(i, 1, n+1)
    {
        cin>>red[i].x>>red[i].y;
        addEdge(0, i, 1 );
    }
    forn(i,1,n+1)
    {
        cin>>blue[i].x>>blue[i].y;
        addEdge(i+n, 2*n+1, 1 );
    }
    forn(i, 1, n+1)
    {
        forn(j, 1, n+1)
        {
            if(red[i].x < blue[j].x && red[i].y < blue[j].y)
            {
                addEdge(i, j+n, 1);
            }
        }
    }
    cout<< dinic(0, 2*n+1) <<endl;


    return 0;
}