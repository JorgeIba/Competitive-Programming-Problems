#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector<lli> > adj;
lli n; 
vector<lli> res;
vector<bool> marked;
vector<bool> visited;
lli maxi = 0;
lli ans = -1;


lli bfs(lli u, bool flag)
{
    vector<lli> parent(n,-1);
    queue<lli> q; q.push(u);

    lli last;
    while(!q.empty())
    {
        last = q.front(); q.pop();
        for(auto v: adj[last])
        {
            if(parent[v] == -1 && v != u)
            {
                parent[v] = last;
                q.push(v);
            }
        }
    }
    lli aux = last;
    
    if(flag)
    {
        marked[u] = true;
        while(aux != u)
        {
            res.push_back(aux);
            marked[aux] = true;
            aux = parent[aux];
        }
        res.push_back(u);
    }
    
    return last;
}

void dfs(lli idx, lli depthParent)
{
    if(visited[idx]) return;
    visited[idx] = true;
    lli depth = depthParent + 1;
    if(depth > maxi)
    {
        maxi = depth;
        ans = idx;
    }
    for(auto v: adj[idx])
    {
        if(!marked[v])
            dfs(v, depth);
    }
    return;
}


int main()
{
    fastIO();
    cin>>n;
    adj.resize(n);
    marked.resize(n, false);
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    lli point1 = bfs(0, false);
    lli point2 = bfs(point1, true);

    if(res.size() == n)
    {
        cout<<n-1<<endl;
        cout<<(point1+1)<<" "<<(point2+1)<<" ";
        for(int i = 0; i<n; i++)
        {
            if(i != point1 && i!= point2)
            {
                cout<<(i+1)<<endl;
                return 0;
            }
        }
    }
    visited.resize(n, false);
    for(int i = 0; i<res.size(); i++)
    {
        dfs(res[i], 0);
    }
    cout<<res.size() - 1 + maxi - 1<< endl;
    cout<<point1+1<<" "<<point2+1<<" "<<ans+1<<endl;
    

    return 0;
}