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
 
vector<vector<lli>> adjList;
vector<lli> bfs(lli s){

    int n = SZ(adjList);

    vector<lli> dist(n, -1);
    queue<lli> q;
    q.push(s);
    dist[s] = 0;

    while(!q.empty()){
        lli u = q.front(); q.pop();

        for(auto v: adjList[u]) {
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}





int main () {
	//fastIO();

    lli n, m, s, t; cin>>n>>m>>s>>t; s--, t--;

    adjList.resize(n);
    vector< vector<lli> > mat(n, vector<lli>(n));
    while(m--) {
        lli u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        mat[u][v] = 1;
        mat[v][u] = 1;

    }

    auto dist_s = bfs(s);

    auto dist_t = bfs(t);
    lli best_way = dist_s[t];
    
    /*
        for(auto x: dist_s) cout << x << " ";
        cout << endl << endl;

        for(auto x: dist_t) cout << x << " ";
        cout << endl << endl;

    
        cout << best_way << endl;
    */
    

    
    lli ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(mat[i][j] || i == j) continue;

            lli new_dist_from_s = min( dist_s[i], dist_s[j] + 1);
            lli new_dist_from_t = min( dist_t[i], dist_t[j] + 1);

        
            // cout << i+1 << " - " << j+1 << "   " <<  new_dist_from_s << " " << new_dist_from_t << " new way: " << new_dist_from_s + new_dist_from_t << endl;;
            

            if(new_dist_from_s + new_dist_from_t < best_way) {
                // ans++;
                // mat[i][j] = 1;
                // mat[j][i] = 1;
            } else {
                ans++;
            }

        }
    }

    cout << ans/2<< endl;
    

	return 0;
}

