#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define fi first
#define se second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


lli n, m; 
vector<vector<pair<lli,lli>>> adjList;
const lli INF = 1e18;

lli techo(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

vector<lli> dijkstra(lli from, lli c)
{
    vector<lli> dist( adjList.size() , INF );

    priority_queue< pair<lli,lli>, vector<pair<lli,lli>>, greater<pair<lli,lli>> > q;
    q.push({0,from}); // {costo, nodo}
    dist[from] = 0;

    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        for(auto v: adjList[u])
        {
            lli new_cost = techo(( c - dist[u] )*v.se, 100);
            // cout << "Costo a: " << v.first << " : " << new_cost << " llegando con: " << dist[u] << endl;

            if( dist[u] + new_cost < dist[v.fi]  )
            {
              dist[v.first] = dist[u] + new_cost;
              q.push({ dist[v.first], v.first});
            }
        }
    }
    return dist;
}





int main () {
    fastIO();
    assert(true);
  cin>>n>>m;
  adjList.resize(n);

  lli s, t, c; cin>>s>>t>>c; s--, t--;

  for(int i = 0; i<m; i++)
  {
    lli u, v, p; cin>>u>>v>>p; u--, v--;
    adjList[u].push_back({v, p});
    adjList[v].push_back({u, p});
  }

  auto anss = dijkstra(s, c);
	

  // for(auto x: anss) cout << x << " ";

    cout << c - anss[t]  << endl;

	return 0;
}

