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

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator<(const point & p) const{return (x < p.x) || (x == p.x && y < p.y);}
};


struct LCA_T{
    const static int maxLOG = 20;
    int n;
    vector<int> depth, order;    
    vector< vector<int> > ancestors;

    template<class G>
    LCA_T(int n, const G &adjList, int root = 1): n(n), depth(n) {
        ancestors.assign(n, vector<int>(maxLOG));
        for(int i = 0; i < n; i++) ancestors[i][0] = i;

        dfs(root, adjList);
        prec();
    }


    template<class G>
    void dfs(int u, const G &adjList, int p = -1) {
    
        order.push_back(u);
        for(auto v: adjList[u]){
            if(v == p) continue;

            ancestors[v][0] = u;
            depth[v] = depth[u] + 1;

            dfs(v, adjList, u);
        }
    }

    void prec() {
        for(auto u: order) 
            for(int i = 1; i < maxLOG; i++) 
                ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
        order.clear();
    }

    int get_kth_parent(int u, int k){
        for(int i = maxLOG - 1; i >= 0; i--) 
            if(k & (1 << i))
                u = ancestors[u][i];

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
};




const int MAXN = 1e5 + 100;

vector<int> adjList[MAXN];


int main () {
	fastIO();
	
    int n; cin>>n;

    vector<point> P(n);
    for(auto &[x, y]: P) 
        cin>>x>>y;

    sort(all(P));

	vector< pair<point, int> > U;
	for(int i = n - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2].first - P[i]).cross(U[U.size()-1].first - P[i]) < 0){
			U.pop_back();
		}
        if(!U.empty()){
            // adjList[i].push_back(U.back().second);
            int p = U.back().second;
            adjList[p].push_back(i);
        }   
            
		U.push_back({P[i], i});
	}

    // forn(i, n){
    //     cout << i << " -> ";
    //     for(auto v: adjList[i]) {
    //         cout << v << ", ";
    //     }
    //     cout << endl;
    // }


    LCA_T LCA(n, adjList, n-1);

    int q; cin>>q;

    forn(test, q){
        int u, v; cin>>u>>v; u--, v--;
        // cout << u << " --> " << v << endl;

        cout << LCA.get_lca(u, v) + 1 << " ";
    }









	return 0;
}

