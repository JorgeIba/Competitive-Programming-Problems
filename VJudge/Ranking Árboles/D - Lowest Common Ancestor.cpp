#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 1e5 + 10, logN = 18;
vector < vector< lli > > adj;
bool visited[maxN];
lli depth[maxN];
vector< vector< lli > > parent;



void dfs(lli u)
{
    assert(!visited[u]);
    visited[u] = true;
    for(auto v: adj[u])
    {
        if(!visited[v])
        {
            depth[v] = depth[u] + 1;
            parent[v][0] =  u;
            for(int i = 1; i<logN; i++)
            {
                parent[v][i] = parent[ parent[v][i-1] ][ i - 1];
            }
            dfs(v);
        }
    }
}


lli queryLCA(lli u, lli v)
{
    if( depth[u] < depth[v]) swap(u,v);
    for(int i = logN; i>=0; i--)
    {
        if(depth[u] >= depth[v] + (1<<i))
        {
            u = parent[u][i];
        }
    } //u y v en el mismo nivel
    assert( depth[u] == depth[v] );
    for(int i = logN; i>=0; i--)
    {
        if( parent[u][i] != parent[v][i] )
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return (u!=v? parent[u][0]: u);
}


int main()
{
    fastIO();
    lli n; cin>>n;
    adj.resize(n);
    parent.assign(n, vector<lli>(20));
    for(int i = 0; i<n; i++)
    {
        lli children; cin>>children;
        for(int j = 0; j<children; j++)
        {
            lli v; cin>>v;
            adj[i].push_back(v);
        }
    }
    dfs(0);
    lli q; cin>>q;
    while(q--)
    {
        lli u, v; cin>>u>>v;
        cout<< queryLCA(u,v) << endl;
    }

    return 0;
}