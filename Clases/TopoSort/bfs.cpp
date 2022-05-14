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


vector<int> toposort_bfs(vector<vector<int>> &adjList){
    int n = adjList.size();
    vector<int> incoming_edges(n);

    for(int i = 0; i < n; i++)
        for(auto v: adjList[i])
            incoming_edges[v]++;

    queue<int> q;
    for(int i = 0; i < n; i++){
        if(incoming_edges[i] == 0) q.push(i);        
    }

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
    if(cnt != n) return {-1};

    return ans;
}


int main () {
	//fastIO();


    int n, m; cin>>n>>m; // n nodos, m aristas

    vector<vector<int>> adjList(n);


    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        u--, v--;
        adjList[u].push_back(v);
        // nodo_u -> nodo_v
    }

    if(hasCycle(adjList)) {
        cout << "NO EXISTE TOPOSORT" << endl;
        return 0;
    }


    vector<int> ans = toposort_bfs(adjList);

    for(auto v: ans) cout << v+1 << " ";



	return 0;
}

