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

string solve()
{
    lli n, k; cin>>n>>k;

    vector<lli> friends(k);
    for(auto &x: friends) cin>>x;
    for(auto &x: friends) x--;

    vector<vector<lli>> adjList(n);
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<lli> leafs;
    for(int i = 1; i<n; i++) 
        if(adjList[i].size() == 1) leafs.push_back(i);


    vector<lli> min_dist(n);
    queue<lli> q;
    vector<bool> visited(n);
    for(auto x: friends)
    {
        q.push(x);
        visited[x] = true;
    }

    /*
    cout << "LEAFS" << endl;
    for(auto x: leafs) cout << x << " ";
    cout << endl;

    cout << "friends" << endl;
    for(auto x: friends) cout << x << " ";
    cout << endl;
    */

    

    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adjList[u])
        {
            if(visited[v]) continue;
            min_dist[v] = min_dist[u] + 1;
            q.push(v);
            visited[v] = true;
        }
    }

    vector<lli> dist(n);
    assert(q.empty());

    q.push(0);

    fill(all(visited), false);
    visited[0] = true;
    while(!q.empty())
    {
        
        lli u = q.front(); q.pop();
        for(auto v: adjList[u])
        {
            if(visited[v]) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
            visited[v] = true;
        }
    }

    /*
    cout << "min_dist" << endl;
    for(auto x: min_dist) cout << x << " ";
    cout << endl;

    cout << "dist" << endl;
    for(auto x: dist) cout << x << " ";
    cout << endl;
    */

    for(auto x: leafs)
    {
        if( dist[x] < min_dist[x] )
        {
            return "YES";
        }
        // assert(dist[x] != min_dist[x]);
    }

    return "NO";
}




int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) cout << solve() << endl;
	


	return 0;
}

