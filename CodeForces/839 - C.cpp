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

VI depth;
vector< VI > adjList;
vector< ld > ev;
//ld ev = 0;

ld dfs(int u, int parent)
{
    int sizeChildren = 0;
    for(auto v: adjList[u])
        if(v != parent) sizeChildren++;

    for(auto v: adjList[u])
    {
        if(v != parent)
        {
            ev[u] += dfs(v, u);
        }
    }

    return ev[u] = sizeChildren? (ld) ev[u] / sizeChildren + 1: 0;
}


int main () {
	//fastIO();
    lli n; cin>>n;
    adjList.resize(n+1);
    depth.resize(n+1);
    ev.resize(n+1);

    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs(1, -1);
    cout << fixed << setprecision(9) <<  ev[1] << endl;
    
	return 0;
}