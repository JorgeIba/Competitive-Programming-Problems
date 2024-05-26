#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

int n, d;
vector< vector<int> > adjList;
vector< int > x_have_to, y_have_to;
vector<bool> x_pass, y_pass;

int dfs_prec_xs(int u, int p = -1){
    int longest = (x_pass[u] ? 0 : -1);
    for(auto v: adjList[u]){
        if( v == p ) continue;
        auto dist = dfs_prec_xs(v, u);

        if(dist != -1){
            longest = max(longest, dist + 1);
        }
    }

    return x_have_to[u] = longest;
}

int dfs_prec_ys(int u, int p = -1){
    int longest = (y_pass[u] ? 0 : -1);
    for(auto v: adjList[u]){
        if( v == p ) continue;
        auto dist = dfs_prec_ys(v, u);

        if(dist != -1){
            longest = max(longest, dist + 1);
        }
    }

    return y_have_to[u] = longest;
}


lli ans = 0;
void dfs(int u, int curr_d, int p = -1){

    vector<lli> both, only_x, only_y;
    for(auto v: adjList[u]){
        if( v == p ) continue;

        auto x_has = (x_have_to[v] != -1);
        auto y_has = (y_have_to[v] != -1);

        if(x_has && y_has){
            both.push_back(v);
        } else if(x_has) {
            only_x.push_back(v);
        } else if(y_has){
            only_y.push_back(v);
        }
    }
    
    for(auto v: both) {
        ans += 2;
        dfs(v, 0, u);
        ans += 2;
    }

    for(auto v: only_x) {
        if(x_have_to[v] + curr_d + 1 > d){
            ans += 2;
            dfs(v, curr_d, u);
            ans += 2;
        } else {
            ans += 1;
            dfs(v, curr_d + 1, u);
            ans += 1;
        }
    }

    for(auto v: only_y) {
        if(y_have_to[v] + curr_d + 1 > d){
            ans += 2;
            dfs(v, curr_d, u);
            ans += 2;
        } else {
            ans += 1;
            dfs(v, curr_d + 1, u);
            ans += 1;
        }
    }

}



int main () {
	//fastIO();
    cin>>n>>d;
    adjList.resize(n+1);
    x_have_to.resize(n+1);
    y_have_to.resize(n+1);
    x_pass.resize(n+1);
    y_pass.resize(n+1);

    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int m_1; cin>>m_1;
    for(int i = 0; i < m_1; i++){
        int x; cin>>x;
        x_pass[x] = true;
    }

    int m_2; cin>>m_2;
    for(int i = 0; i < m_2; i++){
        int y; cin>>y;
        y_pass[y] = true;
    }


    dfs_prec_xs(1);
    dfs_prec_ys(1);


    // for(int i = 1; i <= n; i++) {
    //     cout << i << " -> " << x_have_to[i] << endl;
    // }
    // cout << endl << endl;

    // for(int i = 1; i <= n; i++) {
    //     cout << i << " -> " << y_have_to[i] << endl;
    // }
    // cout << endl << endl;



    dfs(1, 0);
    cout << ans << endl;

	return 0;
}

