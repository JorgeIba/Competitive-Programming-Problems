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
                lli f = 0;
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



vector<int> color;
vector<bool> visited;
vector< vector<lli> > adjList;
void dfs(int u, int color_u) {
    if(visited[u]) return;
    visited[u] = true;

    color[u] = color_u;
    for(auto v: adjList[u]) {
        dfs(v, !color_u);
    }

    return;
}



int main () {
	// fastIO();

    
    int n; 
    cin>>n;
    vector<string> words(n);

    for(auto &x: words) cin>>x;

    color.resize(n);
    visited.resize(n);

    vector<set<string>> cannot(n);

    for(int i = 0; i < n; i++){
        string word = words[i];
        for(int j = 0; j < SZ(word); j++) {
            for(int k = 0; k < j; k++){
                string aux = word;
                swap(aux[j], aux[k]);
                cannot[i].insert(aux);
            }
        }
    }



    adjList.resize(n);
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j) continue;
            if(cannot[i].count(words[j])) {
                adjList[i].push_back(j);
                adjList[j].push_back(i);
            }
        }
    }



    for(int i = 0; i<n; i++)
    {
        if(!visited[i]) {
            dfs(i, 0);
        }
    }

    // for(auto x: color) cout << x << " ";


    Dinic *D = new Dinic(n+5);

    int S = n+2, T = n+3;

    for(int i = 0; i < n; i++){
        if(color[i] == 1){
            D->addEdge(S, i, 1, true);
        } else {
            D->addEdge(i, T, 1, true);
        }
    }


    for(int i = 0; i < n; i++)
    {
        if(color[i] == 0) continue;
        for(auto v: adjList[i]) {
            D->addEdge(i, v, 1, true);
        }
    }


    lli flow = D->StartDinic(S, T);
    // cout << flow << endl;
    cout << n - flow << endl;


	return 0;
}

