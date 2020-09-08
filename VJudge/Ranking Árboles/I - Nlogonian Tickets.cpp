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

const lli logN = 25, INF = 1e18;
vector< vector< Edge* > > adj;
vector< lli > depth;
vector< vector< lli > > parent, cost;

void addEdge(lli u, lli v, lli c)
{
    Edge* uv = new Edge(v, c);
    Edge* vu = new Edge(u, c);
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

void prep(lli n)
{
    adj.clear(); adj.resize(n+1);
    depth.clear(); depth.resize(n+1);
    parent.clear(); parent.assign(n+1, vector<lli>(logN+1));
    cost.clear(); cost.assign(n+1, vector<lli>(logN+1));
}


void dfs(lli u, lli p)
{
    for(auto E: adj[u])
    {
        lli v = E->v, c = E->c;
        if(v != p)
        {
            depth[v] = depth[u] + 1;
            cost[v][0] = c;
            parent[v][0] = u;
            for(int i = 1; i<=logN; i++)
            {
                parent[v][i] = parent[ parent[v][i-1]  ][i-1];
                cost[v][i] = max( cost[v][i-1], cost[ parent[v][i-1]  ][i-1]);
            }
            dfs(v, u);
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
    if(depth[u] < depth[v]) swap(u,v);
    u = getParent(u, depth[u]-depth[v]);
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


lli query(lli u, lli p)
{
    lli res = -INF;
    lli diff = depth[u] - depth[p];
    for(int i = 19; i>=0; i--)
    {
        if(diff & (1<<i))
        {
            res = max(res, cost[u][i]);
            u = parent[u][i];
            diff = depth[u]- depth[p];
        }
    }
    return res;
}



int main()
{
    fastIO();
    while(true)
    {
        lli n; cin>>n;
        if(n==0) return 0;
        prep(n);
        forn(i, 0, n-1)
        {
            lli u, v, c; cin>>u>>v>>c;
            addEdge(u,v,c);
        }
        dfs(1, -1);
        lli q; cin>>q;
        while(q--)
        {
            lli u, v; cin>>u>>v;
            if(depth[u] < depth[v]) swap(u,v);
            lli lca = getLCA(u,v);
            lli UL = query(u, lca);
            if( depth[lca] >= depth[v])
            {
                cout<< UL << endl;
            }
            else
            {
                lli VL = query(v, lca);
                cout << max(UL, VL) << endl;
            }
            
        }
        cout<<endl;
    }

    return 0;
}