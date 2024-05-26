#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MAXN = 1e5 + 100;

vector<int> adjList[MAXN];
vector<int> adjList_T[MAXN];
vector<int> adjList_C[MAXN];

map<int,int> dist_u[MAXN];

vector<int> nodes_in_comp[MAXN];

int comp[MAXN];
bool visited[MAXN];

void dfs_1(int u, vector<int> &order){

    visited[u] = true;
    for(auto v: adjList[u]) {
        if(visited[v]) continue;
        dfs_1(v, order);
    }

    order.push_back(u);
}

void dfs_2(int u, int no_comp){
    nodes_in_comp[no_comp].push_back(u);
    comp[u] = no_comp;

    visited[u] = true;
    for(auto v: adjList_T[u]){
        if(visited[v]) continue;
        dfs_2(v, no_comp);
    }
}

int dp[MAXN];

int f(int y){

    int &ans = dp[y];
    if(ans != -1) return ans;

    ans = 0;
    for(auto new_x: adjList[y]) {
        if(comp[new_x] == comp[y]) continue;

        for(auto new_y: nodes_in_comp[comp[new_x]]) {
            ans = max(ans, (dist_u[new_x][new_y]+1) + f(new_y));
        }
    }

    return ans;
}


int main () {
	fastIO();

    int n, m; cin>>n>>m;

    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList_T[v].push_back(u);
    }

    vector<int> order;
    forn(i, n) if(!visited[i]) {
        dfs_1(i, order);
    }

    reverse(all(order));
    fill(visited, visited + n, false);
    int no_comp = 0;
    for(auto u: order){
        if(visited[u]) continue;
        dfs_2(u, no_comp++);
        assert(SZ(nodes_in_comp[no_comp-1]) <= 5);
    }

    forn(i, n){
        for(auto v: adjList[i]){
            if(comp[i] == comp[v]) {
                adjList_C[i].push_back(v);
            }
        }
    }

    auto distinct = [&](vector<int> nodes){
        return SZ(set<int>(all(nodes))) == SZ(nodes);
    };

    auto bfs = [&](int start){
        map<int,int> dist;
        for(auto a: adjList_C[start]){
            for(auto b: adjList_C[a]) {
                for(auto c: adjList_C[b]){
                    for(auto d: adjList_C[c]){
                        if(distinct({start,a,b,c,d})) {
                            dist[d] = max(dist[d], 4);
                        }
                    }
                    if(distinct({start,a,b,c})) {
                        dist[c] = max(dist[c], 3);
                    }
                }
                if(distinct({start,a,b})) {
                    dist[b] = max(dist[b], 2);
                }
            }
            if(distinct({start,a})) {
                dist[a] = max(dist[a], 1);
            }
        }

        return dist;
    };

    forn(i, n){
        dist_u[i] = bfs(i);
    }


    memset(dp, -1, sizeof(dp));
    int ans = 0;
    forn(i, no_comp) {
        for(auto x: nodes_in_comp[i]){
            for(auto y: nodes_in_comp[i]){
                int ans_u = (dist_u[x][y]+1) + f(y);
                
                ans = max(ans, ans_u);
            }
        }
    }

    cout << ans << endl;

	return 0;
}

