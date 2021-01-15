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
};

vector<lli> poblacion, talisman;
vector< vector<lli> > matrix;
const lli INF = 1e14;
int N, M, T; 
int S = 0, T0; //1 + 0, 1 + 1, 1 + i ... 1 + N-1 IDA
               //(N+1) + 1, (N+1) + 2, (N+1) + 3 ... VUELTA

void precal(){
  forn(k,N){
    forn(u,N){
      forn(v,N){
        matrix[u][v] = min(
          matrix[u][v],
          matrix[u][k] + matrix[k][v]
        );
      }
    }
  }
}



Dinic armarGrafo(lli tiempo)
{
  
  Dinic A(2*(N+1)+10);
  for(int i = 0; i<N; i++)
  {
    for(int j = 0; j<N; j++)
    {
      if(matrix[i][j] <= tiempo)
      {
        A.addEdge(1+i, (N+1) + j, INF);
      }
    }
  }
  for(int i = 0; i<N; i++)
  {
    A.addEdge(S, 1+i, poblacion[i]);
    A.addEdge((N+1)+i, T0, talisman[i]);
  }
  return A;
}


lli min_time(lli se_salvan){
    lli l = 0, r = T;
    lli ans = 0;
    while(l <= r){
        lli mid = (l+r)/2;
        Dinic act = armarGrafo(mid);
        if(act.StartDinic(S, T0) == se_salvan)
        {
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return ans;
}


lli getMaximosSalvan()
{
    Dinic A = armarGrafo(T);
    return A.StartDinic(S, T0);
}


int main () {
	//fastIO();
    cin>>N>>M>>T;
    poblacion.resize(N);
    talisman.resize(N);
    T0 = 2*(N+1) + 5;

    matrix.assign(N, vector<lli>(N, INF));
    for(int i = 0; i<N; i++) matrix[i][i] = 0;

    for(auto &x: poblacion) cin>>x;
    for(auto &x: talisman) cin>>x;

    for(int i = 0; i<M; i++)
    {
        lli u,v,t;
        cin >> u >> v >> t;
        u--; v--;
        matrix[u][v] = min(t, matrix[u][v]);
        matrix[v][u] = min(t, matrix[v][u]);
    }

    precal();
    lli maximosSalvan = getMaximosSalvan();
    lli mn_time = min_time(maximosSalvan);

    cout << mn_time << " " << maximosSalvan << endl;
    
	return 0;
}