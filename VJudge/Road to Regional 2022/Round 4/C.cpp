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

vector<vector<pair<lli,lli>>> adj;

const lli INF = 1e15;
lli dijkstra(lli from, lli to)
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
    return dist[to];
}




int main () {
	//fastIO();

    lli n, m; cin>>n>>m;

    adj.resize(n+1);
    for(int i = 0; i < m; i++) {
        lli u, v; cin>>u>>v;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 1});
    }

    lli ans = dijkstra(1, n);

    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;

	return 0;
}

