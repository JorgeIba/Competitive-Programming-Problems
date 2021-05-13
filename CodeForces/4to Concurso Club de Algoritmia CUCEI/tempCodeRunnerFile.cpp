#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli INF = 1e18;
lli dijkstra(lli from, lli to, vector< vector< pair<lli,lli> > > adj)
{
    vector<lli> dist( adj.size() , INF );

    priority_queue< pair<lli,lli>, vector<pair<lli,lli>>, greater<pair<lli,lli>> > q;
    q.push({0,from}); // {costo, nodo}
    dist[from] = 0;
    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        for(auto v: adj[u])
        {
            if(dist[u] + v.second < dist[v.first])
            {
                dist[v.first] = dist[u] + v.second;
                q.push({ dist[v.first], v.first});
            }
        }
    }
    return (dist[to] >= 1e9? -1: dist[to]);
}

int main () {
	fastIO();
    lli n, m, k; cin>>n>>m>>k;
    vector< vector< pair<lli,lli> > >  adjList(n+5+k); //de 0 a k-1 los modulos, u + k los nodos
    for(int i = 1; i<=n; i++)
    {
        adjList[i+k].push_back({i % k, 1});
        adjList[i%k].push_back({i+k, 1});
    }

    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        if(u==v) continue;
        u+=k, v+=k;
        adjList[u].push_back({v,2});
    }

    lli s, t; cin>>s>>t;
    cout << dijkstra(s+k, t+k, adjList)/2 << endl;


    
	return 0;
}