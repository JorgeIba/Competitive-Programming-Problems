#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adjList;
vector< lli > level, parent;
const lli maxN = 3*(1e5) + 100, LOG = 21;
lli ancestor[maxN][LOG+1];
lli n;

void prep(lli n)
{
    adjList.resize(n+1);
    level.resize(n+1);
    parent.resize(n+1);
}

void dfs(lli u, lli p)
{
    for(auto v: adjList[u])
    {
        if(v != p)
        {
            level[v] = level[u] + 1;
            parent[v] = u;
            ancestor[v][0] = u;
            for(int i = 1; i<LOG; i++)
            {
                ancestor[v][i] = ancestor[ ancestor[v][i-1] ][i-1];
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
            u = ancestor[u][i];
        }
    }
    return u;
}

lli getLCA(lli u, lli v)
{
    if(level[u] < level[v]) swap(u, v);
    u = getKthParent(u, level[u] - level[v]);
    assert(level[u] == level[v]);

    for(int i = LOG-1; i>=0; i--)
    {
        if(ancestor[u][i] != ancestor[v][i])
        {
            u = ancestor[u][i];
            v = ancestor[v][i];
        }
    }
    return ((u!=v)? parent[u]: u);
}


#define dist(u, v) level[u] + level[v] - 2*level[ getLCA(u, v)  ]


int main () {
	fastIO();
    cin>>n;
    prep(n);
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    dfs(1, -1);

    lli q; cin>>q;
    while(q--)
    {
        lli a, b, c; cin>>a>>b>>c;
        if(n == 1) cout << 1 << endl;
        else
        {
            if(c >= dist(a, b))
            {
                cout << b << endl;
            }
            else
            {
                lli lca = getLCA(a, b);
                if(c <= dist(a, lca))
                {
                    cout << getKthParent(a, c) << endl;
                }
                else
                {
                    cout << getKthParent(b, dist(a, b) - c) << endl;;
                }
            }
            
        }
        
    }

	return 0;
}