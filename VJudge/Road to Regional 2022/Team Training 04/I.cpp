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

const int MAXN = 3e5 + 100;

vector<int> adjList[MAXN];

int main () {
	//fastIO();
	
    int n, m; cin>>n>>m;

    forn(i, m) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    vector<bool> reached(n+1, false);

    queue<int> q;
    reached[1] = true;
    vector<int> ans = {1};

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        reached[u] = true;
        ans.push_back(u);

        for(auto v: adjList[u]) {
            if(reached[v]) continue;

            q.push(v);
        }
    }

    for(int i = 1; i <= n; i++) if(!reached[i]) {
        ans.push_back(i);
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;





	return 0;
}

