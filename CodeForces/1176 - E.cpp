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

const int INF = 1e9;

void solve()
{
    int n, m; cin>>n>>m;
    vector<VI> adjList(n+1);
    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    vector<int> odd, even, distance(n+1, INF);
    queue<int> q; q.push(1); distance[1] = 0; even.push_back(1);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(auto v: adjList[u])
        {
            if(distance[v] == INF)
            {
                distance[v] = distance[u] + 1;
                if(distance[v] % 2) odd.push_back(v);
                else even.push_back(v);
                q.push(v);
            }
        }
        
    }
    cout << min(SZ(even), SZ(odd)) << endl;
    if(SZ(even) < SZ(odd))
        for(auto x: even) cout << x << " ";
    else
        for(auto x: odd) cout << x << " ";

    cout << endl;

}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }

	return 0;
}