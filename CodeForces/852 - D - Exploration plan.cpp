#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Edge
{
    lli to, flow, capacity, cost;
    Edge *res;

    Edge(): to(0), flow(0), capacity(0), cost(0) {}
    Edge(lli to, lli capacity, lli cost = 0): to(to), flow(0), capacity(capacity), cost(cost) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

const lli INF = 1e18;
vector< vector< Edge* > > adjList;
vector< lli > distancia, pos, bucket;

void addEdge(lli u, lli v, lli capacity, lli cost)
{
    Edge* uv = new Edge(v, capacity, cost);
    Edge* vu = new Edge(u, 0, cost);    
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

/*
lli Dijsktra(lli s, lli t)
{
    vector<lli> dist(n+1, INF);
    vector<bool> visited(n+1);
    priority_queue< pair<lli,lli>, vector< pair<lli,lli> >, greater<pair<lli,lli>> > q; // costo, nodo
    q.push({0,s});
    dist[s] = 0; 
    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge *E: adjList[u])
        {
            if(dist[E->to] > dist[u] + E->cost)
            {
                dist[E->to] = dist[u] + E->cost;
                q.push({dist[E->to], E->to});
            }
        }
    }
    return dist[t];
}
*/

lli blocking(lli u, lli t, lli flow)
{
    if(u==t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge *E = adjList[u][i];
        if( E-> capacity > E->flow && distancia[E->to] == distancia[u] + 1)
        {
            lli f = blocking(E->to, t, min(flow, E->capacity - E->flow));
            if(f>0)
            {
                E->addFlow(f);
                return f;
            }
        }
    }
    return 0;
}


lli dinic(lli s, lli t)
{
    lli maxFlow = 0;
    distancia[t] = 0;
    while(distancia[t] != -1)
    {
        fill(all(distancia), -1);
        queue<lli> q; q.push(s);
        distancia[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge *E: adjList[u])
            {
                if( distancia[E->to] == -1 && E->capacity > E->flow)
                {
                    distancia[E->to] = distancia[u] + 1;
                    q.push(E->to);
                }
            }
        }
        if(distancia[t] != -1)
        {
            lli f = 0;
            fill(all(pos), 0);
            while(f = blocking(s, t, INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}


const lli maxN = 210, maxV = 650;
lli V, E, N, K; 

lli matrizAdj[maxV][maxV];


void prep(lli n)
{
    adjList.clear(); adjList.resize(2*(n+3));
    pos.clear(); pos.resize(2*(n+3));
    distancia.clear(); distancia.resize(2*(n+3));
}

void FloydWarshall()
{
    for(int k = 1; k<=V; k++)
    {
        for(int i = 1; i<=V; i++)
        {
            for(int j = 1; j<=V; j++)
            {
                matrizAdj[i][j] = min(matrizAdj[i][j], matrizAdj[i][k] + matrizAdj[k][j]);
            }
        }
    }
}

void printMat()
{
    for(int i = 1; i<=V; i++)
    {
        for(int j = 1; j<=V; j++)
        {
            cout<<matrizAdj[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool check(lli t) // 2*i entrada, 2*i+1 salida
{
    prep(V);
    lli S = (V+1), T = (V+2);
    for(int i = 1; i<=V; i++)
    {
        if(bucket[i] > 0)
        {
            for(int j = 1; j<=V; j++)
            {
                if( matrizAdj[i][j] <= t)
                {
                    addEdge(2*i+1, 2*j, INF , 0);
                }
            }
        }
    }
    for(int i = 1; i<=V; i++)
    {
        if(bucket[i] > 0)
        {
            addEdge(2*S+1, 2*i+1, bucket[i], 0);
        }
        addEdge(2*i , 2*T, 1, 0);
    }



    lli res = dinic(2*S+1, 2*T);

    if(res >= K)
    {
        return true;
    }
    return false;
}



int main()
{
    fastIO();
    cin>>V>>E>>N>>K;

    bucket.resize(V+1);
    for(int i = 1; i<=601; i++)
    {
        for(int j = 1; j<=601; j++)
        {
            matrizAdj[i][j] = (i==j? 0: INF);
        }
    }


    for(int i = 0; i<N; i++)
    {
        lli x; cin>>x; bucket[x]++;
    } 
    for(int i = 0; i<E; i++)
    {
        lli u, v, c; cin>>u>>v>>c;
        matrizAdj[u][v] = min(matrizAdj[u][v], c);
        matrizAdj[v][u] = min(matrizAdj[v][u], c);
    }

    FloydWarshall();

    //check(2);

    lli l = 0, r = 1731312, res = -1;;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if( check(mid)  )
        {
            res = mid;
            r = mid-1;
        }
        else
        {
            l = mid + 1;
        }
    }
    
    cout<< res << endl;

    return 0;
}