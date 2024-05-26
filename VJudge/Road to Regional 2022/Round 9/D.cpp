#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


const int maxN = 3e5 + 100;
const int maxLOG = 22;
 
vector< vector<int> > adjList;
vector<int> depth;
int ancestors[maxN][maxLOG];
 
void dfs_prec_lca(int u, int depth_u=0, int p = -1) {
 
    depth[u] = depth_u;
    ancestors[u][0] = p;
    for(int i = 1; i < maxLOG && (1<<i) <= depth_u; i++) {
        ancestors[u][i] = ancestors[ ancestors[u][i-1]   ][i-1];
    }
 
    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_prec_lca(v, depth_u+1, u);
    }
}
 
int get_kth_parent(int u, int k){
    for(int i = maxLOG - 1; i >= 0; i--) {
        if(k & (1 << i)) {
            u = ancestors[u][i];
        }
    }
    return u;
}
 
int get_lca(int u, int v) {
    if(depth[u] > depth[v]) swap(u, v);
    v = get_kth_parent(v, depth[v] - depth[u]);
 
    assert(depth[v] == depth[u]);
 
    for(int i = maxLOG-1; i >= 0; i--) {
        if(ancestors[u][i] != ancestors[v][i]) {
            u = ancestors[u][i];
            v = ancestors[v][i];
        }
    }
 
    return u != v ? ancestors[u][0] : u;
}


void main_(){
    int n; cin>>n;
    adjList.clear();
    adjList.resize(n+1);
    
    depth.clear();
    depth.resize(n+1);

    // YA JALA PTM
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < maxLOG; j++){
            ancestors[i][j] = 0;
        }
    }


    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    dfs_prec_lca(1);


    auto dist = [&](int a, int b) {
        return depth[a] + depth[b] - 2*depth[get_lca(a, b)];
    };


    int q; cin>>q;
    while(q--){
        int k; cin>>k;
        vector<int> nodes(k);
        for(auto &x: nodes) cin>>x;

        int leaf = nodes[0];
        int max_distance = 0, farthest = leaf;
        for(auto v: nodes){
            if(max_distance < dist(leaf, v)) {
                max_distance = dist(leaf, v);
                farthest = v;
            }
        }

        max_distance = 0, leaf = farthest;
        for(auto v: nodes) {
            if(max_distance < dist(farthest, v)) {
                max_distance = dist(farthest, v);
                leaf = v;
            }
        }

        auto ans = true;
        for(auto v: nodes){
            if(dist(leaf, v) + dist(v, farthest) != dist(leaf, farthest))
                ans = false;
        }

        cout << (ans ? "Yes" : "No") << endl;
    }
}

int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

