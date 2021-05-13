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

struct Edge{
    int u, v, w;
    Edge(int u, int v, int w): u(u)

    bool operator<(const Edge A)
    {
        return w < A.w;
    }
};

vector< vector<lli> > adjList;

vector< Edge > Edges;


int main () {
	//fastIO();
    lli n, m; cin>>n>>m;
    adjList.resize(n+1);
    for(int i = 0; i<m; i++)
    {
        lli u, v, w; cin>>u>>v>>w;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        Edges.push_back({})
    }
	



    
	return 0;
}