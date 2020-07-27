typedef pair<lli,lli> pll;
vector<lli> dist;
lli dijkstra(lli from, lli to) //n-> adj size
{
    vector<bool> visited( n ); dist.resize( n, INF );

    priority_queue< pll, vector<pll>, greater<pll> > q;
    
    q.push({0,from}); dist[from] = 0;
    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        if(visited[u]) continue;
        visited[u] = true;
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