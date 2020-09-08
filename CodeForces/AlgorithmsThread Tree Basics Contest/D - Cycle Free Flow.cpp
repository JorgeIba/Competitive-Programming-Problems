#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< pair<lli,lli> > > adjList;
vector< lli > level, parent, cost;
const lli maxN = 3*(1e5) + 100, LOG = 22, INF = 1e18;
lli ancestors[maxN][LOG+1], sparse[maxN][LOG+1];
lli n;

void prep()
{
    adjList.resize(n+1);
    level.resize(n+1);
    parent.resize(n+1);
    cost.resize(n+1);
    for(int i = 0; i<=n; i++)
    {
        for(int j = 0; j<LOG; j++)
        {
            sparse[i][j] = INF;
        }
    }
}

void dfs(lli u, lli p)
{
    for(auto E: adjList[u])
    {
        lli v = E.first, c = E.second;
        if(v!=p)
        {
            level[v] = level[u] + 1;
            parent[v] = u;
            ancestors[v][0] = u;
            //cost[v] = c;
            sparse[v][0] = c;
            for(int i = 1; i<LOG; i++)
            {
                ancestors[v][i] = ancestors[ ancestors[v][i-1]  ][i-1];
                sparse[v][i] = min(sparse[v][i-1], sparse[ ancestors[v][i-1] ][i-1]);
            }
            dfs(v, u);
        }
    }
}

lli getKthParent(lli u, lli k)
{
    for(int i = LOG-1; i>=0; i--)
    {
        if(k & (1<<i))
        {
            u = ancestors[u][i];
        }
    }
    return u;
}

lli getLCA(lli u, lli v)
{
    if(level[u] < level[v]) swap(u, v);
    u = getKthParent(u, level[u] - level[v]);
    assert(level[u] == level[v]);
    for(int i = LOG-1; i >= 0; i--)
    {
        if(ancestors[u][i] != ancestors[v][i])
        {
            u = ancestors[u][i];
            v = ancestors[v][i];
        }
    }
    return ((u!=v)?parent[u]:u);
}

lli query(lli u, lli k)
{
    lli res = INF;
    for(int i = LOG-1; i>=0; i--)
    {
        if(k & (1<<i))
        {
            res = min(res, sparse[u][i]);
            u = ancestors[u][i];
        }
    }
    return res;
}


int main () {
	fastIO();
    lli m;
    cin>>n>>m;
    prep();
    for(int i = 1; i<=n-1; i++)
    {
        lli u, v, w; cin>>u>>v>>w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }
    dfs(1, -1);
    lli q; cin>>q;
    while(q--)
    {
        lli u, v; cin>>u>>v;
        lli LCA = getLCA(u, v);
        lli ans = min(query(u, level[u] - level[LCA]), query(v, level[v] - level[LCA])  );
        //cerr << u << " " << level[u] - level[LCA] << " " << v << " " << level[v] - level[LCA] << endl;
        //cerr << query(u, level[u] - level[LCA]) << " " << query(v, level[v] - level[LCA]) << endl;
        cout << ans << endl;
    }

	return 0;
}