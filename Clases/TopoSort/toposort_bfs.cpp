
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
