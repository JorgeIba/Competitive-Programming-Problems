// Hay que estar seguros que no existe ningun ciclo
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
