#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adj;
lli n; 
lli res = -1;

lli bfs(lli s)
{
    vector<lli> dist(n+1, -1);
    queue<lli> q; q.push(s);
    dist[s] = 0;
    lli last = -1;
    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adj[u])
        {
            if(dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
                last = v;
            }
        }
    }
    res = dist[last];
    return last;
}




int main()
{
    fastIO();
    cin>>n;
    adj.resize(n+1);
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    lli point1 = bfs(1);
    res = 0;
    lli point2 = bfs( point1 );

    //cout<< point1 << " " << point2 << endl;
    cout<< res << endl;

    return 0;
}