#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

vector<vector<lli>> adjList;

vector<lli> bfs(lli start, lli n) {
    vector<lli> dist(n+1, -1);

    queue<lli> q;
    q.push(start);

    dist[start] = 0;
    while(!q.empty()) {
        auto u = q.front(); q.pop();

        for(auto v: adjList[u]) {
            if(dist[v] != -1) continue;
            dist[v] = dist[u] + 1;

            q.push(v);
        }
    }

    return dist;
}



void main_(){
    lli n, m, s, t; cin>>n>>m>>s>>t;
    adjList.resize(n+1);

    set<pair<lli,lli>> exists;

    while(m--) {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        exists.insert({u, v});
        exists.insert({v, u});
    }
    
    auto best_s = bfs(s, n);
    auto best_t = bfs(t, n);
    
    lli dist_best = best_s[t];
    lli ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i+1; j <= n; j++) {
            if(exists.count({i, j})) continue;


            lli new_dist_i_s = min(best_s[i], 1 + best_s[j]);
            lli new_dist_i_t = min(best_t[i], 1 + best_t[j]);

            lli new_dist_j_s = min(best_s[j], 1 + best_s[i]);
            lli new_dist_j_t = min(best_t[j], 1 + best_t[i]);

            lli dist_i = new_dist_i_s + new_dist_i_t;
            lli dist_j = new_dist_j_s + new_dist_j_t;

            // cout << i << " -> " << j << " " << dist_i << " " << dist_j << endl;

            if(dist_i >= dist_best && dist_j >= dist_best) ans++;

        }
    }

    cout << ans << endl;



}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

