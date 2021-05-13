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


int main () {
	fastIO();

    int n; cin>>n;
    vector< vector<lli> > adjList(n+1);
    for(int i = 0; i< n*(n-1)/2; i++)
    {
        int u, v, w; cin>>u>>v>>w;
        adjList[u].push_back(w);
        adjList[v].push_back(w);
    }
    lli sum = 0;
    for(int i = 1; i<=n; i++)
    {
        sort(all(adjList[i]));
        for(int j = 0; j+1<SZ(adjList[i]); j+=2) sum += adjList[i][j+1];
    }
    cout << sum << endl;
    

	return 0;
}