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


vector<int> toposort_bfs(vector<vector<lli>> &adjList, lli start){
    int n = adjList.size();
    vector<int> incoming_edges(n);

    for(int i = 0; i < n; i++)
        for(auto v: adjList[i])
            incoming_edges[v]++;

    queue<int> q;
    q.push(start);

    /*
    for(int i = 0; i < n; i++){
        if(incoming_edges[i] == 0) q.push(i);        
    }
    */

    int cnt = 0;
    vector<int> ans;
    while(!q.empty()){
        int u = q.front(); q.pop();

        ans.push_back(u);
        cnt++;

        for(auto v: adjList[u]){
            incoming_edges[v]--;

            if(incoming_edges[v] == 0){
                q.push(v);
            }
        }
    }

    //HAY UN CICLO
    // if(cnt != n) return {-1};

    return ans;
}


const lli MOD = 1e9 + 7;


int main () {
	//fastIO();

    lli n, m, C; cin>>n>>m>>C;

    vector<vector<pair<lli,lli>>> adjCost(n);
    vector<vector<lli>> adjList(n);

    for(int i = 0; i < m; i++) {
        lli u, v, c; cin>>u>>v>>c; u--, v--;
        adjList[u].push_back(v);
        adjCost[v].push_back({u, c});
    }

    auto toposorted = toposort_bfs(adjList, 0);

    vector<lli> costs(n);
    costs[0] = 1;
    for(int i = 0; i < SZ(toposorted); i++) {
        int u = toposorted[i];
        for(auto [v, c]: adjCost[u]) {
            if(costs[u] > C+100) continue;
            costs[u] += (costs[v] + c);
        }
    }

    vector<lli> valid_costs;
    for(int i = 0; i < n; i++) {
        if(costs[i]) {
            valid_costs.push_back(costs[i]);
        }
    }


        /*
    cout << "Toposort" << endl;
    for(auto v: toposorted) cout << v << " -- ";
    cout << endl;

    cout << "All costs" << endl;
    for(auto x: costs) cout << x << " c ";
    cout << endl;
    
    cout << "Valid costs > 1" << endl;
    for(auto x: costs_valid_greater) cout << x << " ";
    cout << endl;
        */


    lli dp_s[C+1][SZ(valid_costs)+1];
    memset(dp_s, 0, sizeof(dp_s));

    for(int i = 0; i < SZ(valid_costs); i++) dp_s[0][i] = 1;


    for(int coins = 1; coins <= C; coins++) {
        for(int idx = SZ(valid_costs) - 1; idx >= 0; idx--) {
            lli val = valid_costs[idx];

            lli yes = (coins-val >= 0) ? dp_s[coins-val][idx] : 0;
            lli no = (idx+1 < SZ(valid_costs)) ? dp_s[coins][idx+1] : 0;

            dp_s[coins][idx] = (yes + no) % MOD;
        }
    }

    lli ans = 0;
    for(int coins = 1; coins <= C; coins++) {
        (ans += dp_s[coins][0]) %= MOD;
    }

    cout << ans << endl;



	return 0;
}

