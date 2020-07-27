#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli LOG = 17, maxN = 1e5 + 10, INF = 1e9;
bitset<maxN> isCentroid;


vector<lli> adjList[maxN];
lli parents[maxN][LOG+1], depth[maxN], szTree[maxN], ans[maxN], cds[maxN];


void getParents(lli n)
{
    for(int i = 1; i<LOG; i++)
    {
        for(int v = 1; v<=n; v++)
        {
            parents[v][i] = parents[  parents[v][i-1]  ][ i-1 ];
        }
    }
}

void dfs(lli u, lli p)
{
    szTree[u] = 1;
    for(auto v: adjList[u])
    {
        if(v!=p)
        {
            depth[v] = depth[u] + 1;
            parents[v][0] = u;
            dfs(v,u);
            szTree[u] += szTree[v];
        }
    }
}

lli getLCA(lli u, lli v)
{
    if(depth[u] < depth[v]) swap(u,v);
    lli diff = depth[u]-depth[v];
    for(int i = LOG-1; i>=0; i--)
    {
        if(diff & (1<<i))
        {
            u = parents[u][i];
        }
    } // A mismo nivel

    assert(depth[u] == depth[v]);

    for(int i = LOG-1; i>=0; i--)
    {
        if(parents[u][i] != parents[v][i])
        {
            u = parents[u][i];
            v = parents[v][i];
        }
    }

    return (u == v? u: parents[u][0]);
}


lli decomp(lli u)
{
    lli tam = 1;
    for(auto v: adjList[u])
    {
        if(!isCentroid[v]) tam += szTree[u];
    }

    while(true)
    {
        lli ind = -1;
        for(auto v: adjList[u])
        {
            if(!isCentroid[v]  &&  2*szTree[v] > tam)
            {
                ind = v;
            }
        }
        if(ind == -1) break;
        szTree[u] = tam - szTree[ind];
        u = ind;
    }

    isCentroid[u] = true;
    for(auto v: adjList[u])
    {
        if(!isCentroid[v])
        {
            cds[decomp(v)] = u;
        }
    }
    return u;
}


#define dist(u,v) depth[u] + depth[v] - 2*depth[ getLCA(u,v) ]
lli root;

void updateCD(lli u)
{
    lli parent = u;
    while(true)
    {
        ans[parent] = min(ans[parent], dist(u,parent));

        if(parent == root) return;
        parent = cds[parent];
    }
}

lli queryCD(lli u)
{
    lli res = INF;
    lli parent = u;
    while(true)
    {
        res = min(res, ans[parent] + dist(u, parent));

        if(parent == root) return res;
        parent = cds[parent];
    }
}


int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    //prep(n);
    for(int i = 0; i<maxN; i++) ans[i] = INF;
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    dfs(1, 1);
    getParents(n);
    root = decomp(1);
    updateCD(1);
    

    while(m--)
    {
        lli t, u; cin>>t>>u;
        if(t == 1) // update
        {
            updateCD(u);
        }
        else
        {
            cout<<queryCD(u)<<endl;
        }
    }
    return 0;
}
