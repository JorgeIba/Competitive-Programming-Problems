#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


const int MOD = 998244353;

int main () {
	// fastIO();

    int n, m; cin>>n>>m;

    set<int> availables;
    vector< set<int> > not_allowed(n);

    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        not_allowed[u].insert(v);
        not_allowed[v].insert(u);
    }


    vector<int> dist(n, -1);
    vector< vector<int> > u_per_dist(n);
    queue<int> q;

    q.push(0); dist[0] = 0;

    forr(i, 1, n-1) availables.insert(i);

    while(!q.empty()){
        auto u = q.front(); q.pop();

        u_per_dist[dist[u]].push_back(u);

        vector<int> to_remove;
        for(auto v: availables){
            if(not_allowed[u].count(v)) continue;

            dist[v] = dist[u] + 1;
            to_remove.push_back(v);
            q.push(v);
        }

        for(auto v: to_remove){
            availables.extract(v);
        }
    }


    if(dist[n-1] == -1){
        cout << -1 << endl;
        return 0;
    }

    vector<int> all_ways(n);
    vector<int> ways(n);

    ways[0] = 1;
    all_ways[0] = 1;

    for(int d = 1; d < n; d++) {
        for(auto u: u_per_dist[d]) {
            ways[u] = all_ways[d-1];

            for(auto v: not_allowed[u]){
                if(dist[v] != dist[u] - 1) continue;
                ways[u] -= ways[v];
                if(ways[u] < 0) ways[u] += MOD;
            }
        }

        for(auto u: u_per_dist[d]){

            all_ways[d] += ways[u];
            if(all_ways[d] >= MOD) all_ways[d] -= MOD;
        }
    }


    cout << ways[n-1] << endl;


	return 0;
}

