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


const int MAXN = 1e5+100;

vector<int> adjList[MAXN];

int main () {
	//fastIO();
	
    int n, m; cin>>n>>m;

    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    vector<bool> visited(n);
    auto dfs = [&](const auto &dfs, int u, vector<int> &comps) -> void {
        if(visited[u]) return; 
        visited[u] = true;

        comps.push_back(u);
        for(auto v: adjList[u]){
            dfs(dfs, v, comps);
        }
    };

    vector<int> colors(n, -1);
    auto bfs = [&](int start){
        queue<int> q;
        q.push(start);
        colors[start] = 0;

        bool ok = true;
        while(!q.empty()){
            auto u = q.front(); q.pop();

            for(auto v: adjList[u]){
                if(colors[v] != -1){
                    if(colors[u] == colors[v]) ok = false;
                    continue;
                }

                colors[v] = colors[u]^1;
                q.push(v);
            }
        }

        return ok;
    };

    vector<int> left_side, right_side;
    forn(i, n){
        if(visited[i]) continue;

        vector<int> comp;
        dfs(dfs, i, comp);

        // cout << i << " -> " << endl;
        // for(auto u: comp) cout << u << ", ";
        // cout << endl;

        auto ok = bfs(comp[0]);


        // for(auto u: comp){
        //     cout << colors[u] << ", ";
        // }
        // cout << endl;


        if(!ok){
            cout << -1 << endl;
            return 0;
        }

        for(auto u: comp){
            if(colors[u] == 0) left_side.push_back(u);
            else if(colors[u] == 1) right_side.push_back(u);
            else assert(false);
        }
    }

    cout << SZ(left_side) << endl;
    for(auto u: left_side){
        cout << u+1 << " ";
    }
    cout << endl;

    cout << SZ(right_side) << endl;
    for(auto u: right_side){
        cout << u+1 << " ";
    }
    cout << endl;






	return 0;
}


