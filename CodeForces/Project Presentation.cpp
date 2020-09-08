#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int n, m;
const int LOG = 20, maxN = 1000005;
int colors[maxN], depth[maxN];
int ancestors[maxN][LOG];
vector<int> adjList[maxN], assigns[maxN];

void dfs(int u, int p)
{
    int color = colors[u];
    assigns[color].push_back(u);
    for(auto v: adjList[u])
    {
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int getLCA(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = LOG-1; i>=0; i--)
    {
        if(  diff & (1<<i) )
        {
            u = ancestors[u][i];
        }
    }
    for(int i = LOG-1; i>=0; i--)
    {
        if(ancestors[u][i] != ancestors[v][i])
        {
            u = ancestors[u][i];
            v = ancestors[v][i];
        }
    }

    return u!=v? ancestors[u][0]: u;
}


int main()
{
    fastIO();
    cin>>n>>m;
    for(int i = 1; i<=n; i++) cin>>colors[i];
    int root = -1;
    for(int i = 1; i<=n; i++)
    {
         cin>>ancestors[i][0];
         if(ancestors[i][0] == 0)
         {
            root = i;
            continue;
         }
         adjList[ancestors[i][0]].push_back(i);
    }

    for(int i = 1; i<=n; i++)
    {
        for(int k = 1; k<LOG; k++)
        {
            ancestors[i][k] = ancestors[ ancestors[i][k-1]  ][k-1];
        }
    }

    dfs(root, -1);
    for(int i = 1; i<=m; i++)
    {
        int suma = 0, lca = -1, anterior = -1;
        for(int j = 0; j<assigns[i].size(); j++)
        {
            int actual = assigns[i][j];
            if(j == 0)
            {
                suma = depth[actual] + 1;
            }
            else
            {
                int LCA = getLCA(actual, anterior);
                int dist = depth[actual] - depth[LCA] ;
                suma += dist;
            }
            anterior = actual;
        }
        //if(i == 2) cout << suma << endl;
        cout << suma << " ";
    }

    

    return 0;
}