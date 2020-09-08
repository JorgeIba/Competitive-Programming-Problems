#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adjList;
lli n; 
lli diameter = 0;

lli bfs(lli s, bool diam)
{
    vector< lli > dist(n+1, -1);
    queue<lli> q; q.push(s);
    dist[s] = 0;
    lli farthest = -1;
    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adjList[u])
        {
            if(v != u && dist[v] == -1)
            {
                //cerr << v << " " << u << endl;
                dist[v] = dist[u] + 1;
                farthest = v;
                q.push(v);
            }
        }
    }
    if(diam)
    {
        diameter = dist[farthest];
    }
    return farthest;
}


int main () {
	fastIO();
    cin>>n;
    if(n == 1)
    {
        puts("0");
        return 0;
    }
    adjList.resize(n+1);
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    lli point1 = bfs(1, false);
    bfs(point1, true);

    cout << (lli)(3*diameter) << endl;


	return 0;
}