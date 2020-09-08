#include <bits/stdc++.h>

#define lli int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

struct Edge{
    lli to, flow, capacity;
    Edge* res;
    Edge(int to, lli capacity, lli cost = 0): to(to), flow(0), capacity(capacity) {}
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
    lli limit = 1;
    bool scaling;
    const lli INF = numeric_limits<lli>::max();

    Dinic(lli N, bool withScaling = false): N(N), scaling(withScaling) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, lli capacity, bool directed = false)
    {
        Edge* uv = new Edge(v, capacity);
        Edge* vu = new Edge(u, directed?0:capacity); // change 0 for capacity if is undirected
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    lli BlockingFlow(int u, int t, lli flow)
    {
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ )
        {
            Edge* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1)
            {
                lli f = BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0)
                {
                     E->addFlow(f); 
                     return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t)
    {
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* E: adjList[u])
            {
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit))
                {
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    lli StartDinic(int s, int t)
    {
        lli maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1) // (1<<30) is for maximum capacity = 10^9
        {
            dist[t] = 0;
            while(bfs(s, t))
            {
                int f = 0;
                fill(all(pos), 0);
                while((f = BlockingFlow(s, t, INF)))
                {
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }
    //Remember: To found Min Cut, do a dfs with residual graph and check just edges that aren't saturated
    //Min Cut will be edges that go through visited node to unvisited node
};


bool isDominated(vector< lli > &a, vector< lli > &b, lli k)
{
    if(a == b) return false;
    for(int i = 1; i<=k; i++)
    {
        if(a[i] > b[i]) return false;
    }
    return true;
}
const lli maxN = 1005;
vector<int> values[maxN];
int f[maxN];
Dinic *D;

/*
    Separate in two independent sets, with ones and zeros. And all of vectors with f == 1 have to be greater or equal than set of zeros
*/
bool visited[maxN];

void dfs(lli u)
{
    if(visited[u]) return;
    visited[u] = true;
    for(Edge* E: D->adjList[u])
    {
        if(E->capacity == E->flow) continue;
        else dfs(E->to);
    }
}

int main () {
	lli n, k; cin>>n>>k;
    for(int i = 1; i<=n; i++) values[i].resize(k+1);
    for(int i = 1; i<=n; i++)
    {
        for(int j = 1; j<=k; j++) cin>>values[i][j];
        cin>>f[i];
    } 

    D = new Dinic(n+5);

    int s = 0, t = n+1;

    for(int i = 1; i<=n; i++)
    {
        if(f[i] == 1){ D->addEdge(s, i, 1, true); } //s to ones
        else { D->addEdge(i, t, 1, true); } // zeros to t

        for(int j = 1; j<=n; j++)
        {
            if(isDominated(values[i], values[j], k) && f[i] == 1) //Hay o puede haber pedos
            {
                D->addEdge(i, j, 1, true);
            }
        }
    }

    cout << D->StartDinic(s, t) << endl;

    dfs(s);
    vector<lli> ans;
    for(int i = 1; i<=n; i++)
    {
        if((f[i] == 0 && visited[i]) || (f[i] == 1 && !visited[i]))
        {
            ans.push_back(i);
        }
    }
    for(auto x: ans) cout << x << " ";
        

	return 0;
}