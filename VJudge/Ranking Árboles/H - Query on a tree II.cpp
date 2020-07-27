#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


struct Edge
{
    lli v, c;
    Edge(lli v, lli c): v(v), c(c) {}
};

vector< vector < Edge* > > adj;

void addEdge(lli u, lli v, lli c)
{
    Edge *uv = new Edge(v, c);
    Edge *vu = new Edge(u, c);
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

const lli logN = 16;
vector< bool > visited;
vector< vector< lli > > parent;
vector< lli > depth, prefCosts;


void prep(lli n){
    adj.clear(); adj.resize(n+1); 
    visited.clear(); visited.resize(n+1);
    parent.clear(); parent.assign(n+1, vector<lli> (logN+1));
    depth.clear(); depth.resize(n+1, 0);
    prefCosts.clear(); prefCosts.resize(n+1, 0);
}


void dfs(lli u)
{
    assert(!visited[u]);
    visited[u] = true;
    for(auto E: adj[u])
    {
        lli v = E->v, c = E->c;
        if( !visited[v]  )
        {
            prefCosts[v] = prefCosts[u] + c; //Prefijo suma
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            for(int i = 1; i<logN; i++)
            {
                parent[v][i] = parent[ parent[v][i-1]   ][i-1];
            }
            dfs(v);
        }
    }
}

lli getParent(lli u, lli k) //k-th parent
{
    lli depthK = depth[u] - k;
    for(int i = logN; i>=0; i--)
    {
        if(depth[u] >= depthK + (1<<i))
        {
            u = parent[u][i];
        }
    }
    return u;
}


lli getLCA(lli u, lli v)
{
    if( depth[u] < depth[v]) swap(u, v);
    u = getParent(u, depth[u] - depth[v]);
    assert(depth[u] == depth[v]);
    for(int i = logN; i>=0; i--)
    {
        if(parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return (u!=v? parent[u][0]: u);
}



void solve()
{
    lli n; cin>>n; //*lo voy a rootear en 1
    prep(n);
    forn(i,0,n-1)
    {
        lli u, v, c; cin>>u>>v>>c;
        addEdge(u,v,c);
    }
    dfs(1);
    while(true)
    {
        string t; cin>>t;
        if(t == "DIST")
        {
            lli u, v; cin>>u>>v;
            lli lca = getLCA(u,v);
            lli res =  prefCosts[u] - prefCosts[lca];
            res += ( prefCosts[v] - prefCosts[ lca ]);
            cout<< res <<endl;
        }
        else if (t == "KTH")
        {
            lli u, v, k; cin>>u>>v>>k;
            lli lca = getLCA(u,v);
            lli UL = depth[u] - depth[lca] + 1;
            lli lV = depth[v] - depth[lca];
            if( k <= UL )
            {
                cout<< getParent(u, k-1) << endl;
            }
            else
            {
                k -= UL;
                cout<< getParent(v, lV - k) <<endl;
            }
        }
        else
        {
            cout<<endl;
            return;
        }
    }
}

int main()
{
    fastIO();
    lli t; cin>>t;
    //lli t = 1;
    while(t--)
        solve();
    return 0;
}