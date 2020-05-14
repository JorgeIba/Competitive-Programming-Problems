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
    lli to, flow, capacity, ix, iy;
    Edge* res;
    Edge(lli to, lli flow, lli capacity, lli ix, lli iy): to(to), flow(flow), capacity(capacity), ix(ix), iy(iy) {}
    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

//lli adjList[51][51][2]; // i,0 va a j,1 ... 0->salida, 1->entrada
vector< vector<Edge*> > adjList;
const lli INF = numeric_limits<int>::max();
lli s, t;
vector< string > mat;
vector< lli > dis;
vector<lli> pos;
lli n, m; 


void addEdge(lli u, lli v, lli capacity, lli ix, lli iy)
{
    Edge* uv = new Edge(v, 0, capacity, ix, iy);
    Edge* vu = new Edge(u, 0, 0, ix, iy);
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
            while(f=blockingFlow(s, t, INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;   
}


lli mappeo(lli i,lli j)
{
    return i*2*m + 2*j;
}

void addAdj(lli i, lli j)
{
    vector< pair<lli,lli> > dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    if(mat[i][j] == '.')
    {
        addEdge(mappeo(i,j), mappeo(i,j)+1, 1, i, j);
    }
    else
    {
        addEdge(mappeo(i,j), mappeo(i,j)+1, INF, i, j);
    }
    for(pair<lli,lli> a:  dir)
    {
        lli di = a.first, dj = a.second;
        if(0<= i+di && i+di < n && 0<=j+dj && j+dj < m && mat[i+di][j+dj] != '#')
        {
            addEdge( mappeo(i,j) + 1, mappeo(i+di,j+dj), INF, i, j);
            /*
            if(mat[i+di][j+dj] == '.')
            {
                addEdge( mappeo(i+di,j+dj), mappeo(i+di,j+dj) + 1, 1);
            }
            else
            {
                addEdge( mappeo(i+di,j+dj), mappeo(i+di,j+dj) + 1, INF);    
            }
            */
        }
    }
}

vector<bool> visited;

void dfs(lli u)
{
    if(visited[u]) return;
    visited[u] = true;
    for(Edge* v: adjList[u])
    {
        if(v->capacity == v->flow) continue;
        else
        {
            dfs(v->to);
        }
    }
}


int main()
{
    fastIO();
    cin>>n>>m;
    mat.resize(n);
    adjList.resize(n*m*2);
    visited.resize(n*m*2, false);
    pos.resize(n*m*2);
    dis.resize(n*m*2);
    forn(i,0,n)
    {
        cin>>mat[i];
    }
    forn(i,0,n)
    {
        forn(j,0,m)
        {
            if(mat[i][j] == 'A') s = mappeo(i,j);
            if(mat[i][j] == 'B') t = mappeo(i,j)+1;
            if(mat[i][j] != '#') addAdj(i,j);
        }
    }
    lli maxFlow = dinic(s,t);
    if(maxFlow >= INF)
    {
        cout<<-1<<endl;
    }
    else
    {
        cout<<maxFlow<<endl;
        dfs(s);
        for(int i = 0; i<n*m*2; i++)
        {
            if(!visited[i]) continue;
            for(Edge* v: adjList[i])    
            {
                if(!visited[v->to] && v->capacity == v->flow && v->flow == 1) 
                {
                    lli x = v->ix, y = v->iy;
                    mat[x][y] = '+';
                }
            }
        }
        forn(i,0,n)
        {
            cout<<mat[i]<<endl;
        }
    }
    

    return 0;
}