#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adjList;
vector< lli > parent, level;
const lli maxN = 3*(1e5) + 100, LOG = 21;
lli ancestor[maxN][LOG+1];
lli n, p1, p2;

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
                ancestor[v][i] = ancestor[ ancestor[v][i-1]  ][i-1];
            }
            dfs(v, u);
        }
    }
}

void prep(lli n)
{
    adjList.resize(n+1);
    level.resize(n+1);
    parent.resize(n+1);
}
lli diameter = 0;
lli bfs(lli s, bool diam)
{
    vector< lli > dist(n+1, -1);
    queue<lli> q; q.push(s);
    dist[s] = 0;
    lli farthest = -1;
    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adjList[u])
        {
            if(v != u && dist[v] == -1)
            {
                //cerr << v << " " << u << endl;
                dist[v] = dist[u] + 1;
                farthest = v;
                q.push(v);
            }
        }
    }
    if(diam)
    {
        diameter = dist[farthest];
    }
    return farthest;
}


lli getDiameter()
{
    p1 = bfs(1, false);
    p2 = bfs(p1, true);
    return diameter;
}

lli getLCA(lli u, lli v)
{
    if(level[u] < level[v]) swap(u, v);
    lli diff = level[u] - level[v];
    for(int i = LOG; i>=0; i--)
    {
        if( diff & (1<<i) )
        {
            u = ancestor[u][i];
        }
    }
    assert(level[u] == level[v]);

    for(int i = LOG; i>=0; i--)
    {
        if(ancestor[u][i] != ancestor[v][i])
        {
            u = ancestor[u][i];
            v = ancestor[v][i];
        }
    }

    return (u!=v? parent[u]: u);
}

#define dist(u, v) level[u] + level[v] - 2 * level[ getLCA(u, v) ]

int main () {
	fastIO();
    cin>>n;
    if(n == 1)
    {
        puts("1");
        return 0;
    }
    prep(n);
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs(1, -1);

    getDiameter();
    cerr << p1 << " " << p2 << endl;

    for(int i = 1; i<=n; i++)
    {
        lli dist1 = dist(p1, i);
        lli dist2 = dist(p2, i);
        //cerr << dist1 << " " << dist2 << endl;
        if((dist1 == diameter) || (dist2 == diameter))
        {
            cout << (diameter+1) << endl;
        }
        else
        {
            cout << diameter << endl;
        }
    
    }

	return 0;
}