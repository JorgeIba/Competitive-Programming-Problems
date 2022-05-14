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


bool hasCycleUtil(int me, vector<int> &state, vector<vector<int>> &graph){
	if(state[me] == 1) return true;
	if(state[me] == 2) return false;
	state[me] = 1;

	bool sol = false;
	for(auto child:graph[me]){
		sol = sol || hasCycleUtil(child, state, graph);
	}
	state[me] = 2;

	return sol;
}

bool hasCycle(vector<vector<int>> &graph)
{
    int n = graph.size();
	vector<int> state(n, 0);
	bool ans = false;
	for(int i=0; i<n; i++){
		if(state[i] == 0) ans = ans || hasCycleUtil(i, state, graph);
	}
    return ans;
}   


void dfs(int currentNode, vector<bool> &visited, vector<vector<int>> &adjList, vector<int> &ans){

    if(visited[currentNode]) return;
    visited[currentNode] = true;

    for(auto nextNode: adjList[currentNode]){ // ME ASEGURA DE QUE YA PUSE TODAS MIS ARISTAS
        dfs(nextNode, visited, adjList, ans);
    }

    ans.push_back(currentNode);
    return;
}

vector<int> toposort_dfs(vector<vector<int>> &adjList){
    int n = adjList.size();
    vector<bool> visited(n);
    vector<int> ans;

    for(int i = 0; i < n; i++)
    {
        if(!visited[i]){
            dfs(i, visited, adjList, ans);
        }
    }
    reverse(ans.begin(), ans.end());
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



    vector<int> ans = toposort_dfs(adjList);

    for(auto v: ans) cout << v+1 << " ";





	return 0;
}

