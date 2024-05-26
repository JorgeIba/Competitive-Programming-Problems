#include<bits/stdc++.h>
#define se second
#define fi first
#define forn(i,n) for(int i = 0; i < n; i++)

using namespace std;
typedef pair<int,int> pii;

int R, C, F, S;
vector<vector<pii>> adj;

int dis(pii a, pii b) {
	return abs(a.fi - b.fi) + abs(a.se - b.se);
}

int dijkstra(int from, int to) {
	const int inf = 1e9;
	vector<int> dist(adj.size(), inf);

	priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > q;
	q.push({0,from}); // {costo, nodo}
	dist[from] = 0;
	while(!q.empty()) {
			int u = q.top().second; q.pop();
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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> R >> C >> F >> S;
	adj.resize(S+2);
	vector<pii> points;
	map<pii, int> aux;
	forn(i,S) {
		int u, v;
		cin >> u >> v;
		points.push_back({u,v});
		aux[{u,v}] = i;
	}
	aux[{1,1}] = S;
	aux[{R,C}] = S+1;
	points.push_back({1,1});
	points.push_back({R,C});
	for(int i = 0; i < points.size() - 1; i++) {
		for(int j = i+1; j < points.size(); j++) {
			int cost = dis(points[i], points[j]);
			if(cost <= F) {
				int u = aux[points[i]];
				int v = aux[points[j]];
				adj[u].push_back({v,cost});
				adj[v].push_back({u,cost});
			}
		}
	}
	/*for(auto x : aux) cout << "{" << x.fi.fi << "," << x.fi.se << "} : " << x.se << '\n';
	forn(i,S+2) {
		cout << i << ": ";
		for(auto v : adj[i]) cout << v.fi <<  ' '; cout << '\n';
	}*/
	cout << dijkstra(S, S+1) << '\n';
	return 0;
}