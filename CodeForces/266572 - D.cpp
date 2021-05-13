#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

/*
    When all capacities are the unity: O(n*sqrt(n))
    General without scaling: O(V^2*E)
    General with scaling:  O(E*V*log(U)) where U is maximum flow
*/

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

    void addEdge(int u, int v, lli capacity, bool directed = true)
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

    //To found if a edge is part of min-cut
    //Run dfs(S) and if U is part of T and is
    //visited, then is part of min-cut
    vector<bool> visited;
    void dfs(int u, bool clearing = true) 
    {
        if(clearing) visited.resize(N);
        if(visited[u]) return;
        visited[u] = true;
        for(auto E: adjList[u])
        {
            if(E->capacity == E->flow) continue;
            dfs(E->to, false);
        }
    }
};

bool isDominated(const vector<int> &a, const vector<int> &b)
{
    for(int i = 0; i<SZ(a); i++)
        if(a[i] > b[i]) return false;
    return true;
}


const int INF = 1e9;

int main () {
	fastIO();
    lli n, k; cin>>n>>k;
    vector<vector<int>> vectors(n, vector<int>(k));
    vector<int> f(n);

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<k; j++)
        {
            cin>>vectors[i][j];
        }
        cin>>f[i];
    }

    int s = n, t = n+1;
    Dinic D(n+2);

    for(int i = 0; i<n; i++)
    {
        if(f[i] == 1) D.addEdge(s, i, 1);
        else D.addEdge(i, t, 1);

        for(int j = 0; j<n; j++)
        {
            if(f[i] == 1 && f[j] == 0 && isDominated(vectors[i], vectors[j]))
            {
                D.addEdge(i, j, INF);
            }
        }
    }

    cout << D.StartDinic(s, t) << endl;

    D.dfs(s);

    vector<int> ans;
    for(int i = 0; i<n; i++)
    {
        if((f[i] == 1 && !D.visited[i]) || (f[i] == 0 && D.visited[i])) ans.push_back(i+1);
    }
        

    for(auto v: ans) cout << v << " ";

    
	return 0;
}