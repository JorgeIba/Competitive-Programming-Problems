#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


vector< vector<int> > adjList;

int ans = 0;


int dfs(int u, int p) {
    
    if(SZ(adjList[u]) == 1 && p != -1) return 0;

    int longest = 0;
    for(auto v: adjList[u]) {
        if(v == p) continue;

        int longest_v = dfs(v, u) + 1;

        ans = max(ans, longest + longest_v);

        longest = max(longest, longest_v);
    }

    return longest;
}



int main () {
	fastIO();
	
    int n; cin>>n;

    adjList.resize(n+1);

    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    dfs(1, -1);

    cout << 3*ans << endl;


	return 0;
}
