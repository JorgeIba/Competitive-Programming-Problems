#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int MAXN = 1e5 + 10;
vector<int> adjList[MAXN];



int main () {
	fastIO();
	
    int n, m; cin>>n>>m;

    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        // adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> incoming_edges(n);
    for(int i = 0; i < n; i++)
        for(auto v: adjList[i])
            incoming_edges[v]++;

    priority_queue<int, vector<int>> pq;

    for(int i = 0; i < n; i++){
        if(incoming_edges[i] == 0) pq.push(i);
    }

    int cnt = n;
    vector<int> ans(n);
    while(!pq.empty()){
        int u = pq.top(); pq.pop();
        ans[u] = cnt--;

        for(auto v: adjList[u]){
            incoming_edges[v]--;

            if(incoming_edges[v] == 0){
                pq.push(v);
            }
        }
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;

	return 0;
}

