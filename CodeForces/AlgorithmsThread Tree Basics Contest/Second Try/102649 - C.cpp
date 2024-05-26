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


const int maxN = 3e5 + 100;
const int maxLOG = 20;

vector< vector<int> > adjList;
vector<int> depth, parent, order;
int ancestors[maxN][maxLOG];

void dfs_prec(int u, int depth_u=0, int p = -1) {
    parent[u] = p;
    depth[u] = depth_u;
    order.push_back(u);

    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_prec(v, depth_u+1, u);
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

    for(int i = maxLOG-1; i >= 0; i--) {
        if(ancestors[u][i] != ancestors[v][i]) {
            u = ancestors[u][i];
            v = ancestors[v][i];
        }
    }

    return u != v ? ancestors[u][0] : u;
}


void prec_lca() {
    for(auto u: order) {
        ancestors[u][0] = parent[u];
    }

    for(auto u: order) {
        for(int i = 1; i < maxLOG && (1<<i) <= depth[u]; i++) {
            ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
        }
    }
}




int main () {
	fastIO();

    int n; cin>>n;

    adjList.resize(n+1);
    depth.resize(n+1);
    parent.resize(n+1);

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    dfs_prec(1);
    prec_lca();


    auto get_dist = [&](int a, int b) {
        return depth[a] + depth[b] - 2*depth[get_lca(a, b)];
    };

    int q; cin>>q;

    while(q--) {
        int a, b, c; cin>>a>>b>>c;
        int lca_a_b = get_lca(a, b);


        int dist = get_dist(a, b);
        if(dist <= c) {
            cout << b << endl;
        } else if( get_dist(a, lca_a_b) >= c) {
            cout << get_kth_parent(a, c) << endl;
        } else {
            c -= get_dist(a, lca_a_b);
            c = get_dist(b, lca_a_b) - c;
            
            cout << get_kth_parent(b, c) << endl;
        }

    }



	return 0;
}

