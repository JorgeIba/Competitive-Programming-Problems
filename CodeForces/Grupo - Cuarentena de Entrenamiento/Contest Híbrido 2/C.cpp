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
	//fastIO();

    lli n; cin>>n;

    vector<vector<lli>> adjList(n+1);

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v; 
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    vector<lli> color(n+1, -1);

    queue<lli> q;
    q.push(1);
    color[1] = 1;

    while(!q.empty()) {
        lli u = q.front(); q.pop();
    
        for(auto v: adjList[u]) {
            if(color[v] != -1) continue;
            color[v] = !color[u];
            q.push(v);
        }
    }


    vector<lli> left, right;

    for(int i = 1; i <= n; i++) {
        if(color[i] == 0) left.push_back(i);
        else right.push_back(i);
    }


    lli sum = 0; 


    for(int i = 0; i < SZ(left); i++) {
        lli u = left[i];
        lli rest = SZ(right) - SZ(adjList[u]);
        sum += rest;
    }


    cout << sum << endl;


	return 0;
}

