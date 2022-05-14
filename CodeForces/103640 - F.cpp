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


vector<bool> visited;
vector< vector<lli> > adjList;

void dfs(int u) {
    if(visited[u]) return;
    visited[u] = true;

    for(auto v: adjList[u])
        dfs(v);
}

int main () {
	//fastIO();
    int n, m; cin>>n>>m;

    adjList.resize(n+1);
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;

        if(u == n || v == n) continue;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    visited.resize(n+1);
    dfs(n-1);

    for(int i = 1; i <= n; i++){
        if(visited[i]){
            cout << "B";
        } else {
            cout << "A";
        }
    }
    cout << endl;



	return 0;
}

