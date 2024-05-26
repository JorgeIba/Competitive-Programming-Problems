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


const int MAXN = 1e5 + 100;
const int LOG  = 20;
const int MAXA = 1e6 + 100;

vector<int> adjListVT[MAXN];
int ancestor[MAXN][LOG];
int depth[MAXN];
array<int,2> rang[MAXN];
int Time = 0;

struct VirtualTreeMaker{

    VirtualTreeMaker() {}

    template<class G>
    void build(const G &adjList, int root = 0){
        dfs_prec(root, root, adjList);
    } 

    template<class G>
    void dfs_prec(int u, int p, const G &adjList){
        // Precalculate ancestors
        ancestor[u][0] = p;
        for(int i = 1; i < LOG; i++){
            ancestor[u][i] = ancestor[ancestor[u][i-1]][i-1];
        }

        // DFS order
        rang[u][0] = Time++;
        for(auto v: adjList[u]){
            if(v == p) continue;
            depth[v] = depth[u] + 1;
            dfs_prec(v, u, adjList);
        }

        rang[u][1] = Time - 1;
    }

    bool is_above(int u, int v){
        return rang[u][0] <= rang[v][0] && rang[v][1] <= rang[u][1];
    }

    int get_lca(int u, int v){
        if(is_above(u, v)) return u;
        if(is_above(v, u)) return v;

        for(int i = LOG-1; i >= 0; i--){
            if(!is_above(ancestor[u][i], v)) {
                u = ancestor[u][i];
            }
        }
        return ancestor[u][0];
    }

    vector<int> virtual_tree(vector<int> nodes){
        if(nodes.empty()) return {};

        sort(all(nodes), [&](auto u, auto v){
            return rang[u][0] < rang[v][0];
        });

        int n = SZ(nodes);
        for(int i = 0; i < n-1; i++){
            int u = nodes[i], v = nodes[i+1];
            int lca = get_lca(u, v);
            nodes.push_back(lca);
        }

        sort(all(nodes), [&](auto u, auto v){
            return rang[u][0] < rang[v][0];
        });

        nodes.erase(unique(all(nodes)), nodes.end());
        for(auto u: nodes) adjListVT[u].clear();

        stack<int> s;
        s.push(nodes.front());

        for(int i = 1; i < SZ(nodes); i++){
            auto u = nodes[i];
            while(!is_above(s.top(), u)) s.pop();

            adjListVT[s.top()].push_back(u);
            s.push(u);
        }  

        return nodes;
    }


    int get_first_active_ancestor(int u, const vector<int> &relevant_nodes){
        int n = SZ(relevant_nodes);
        int l = 0, r = n-1, ans = -1;
        while(l <= r) {
            int mid = (l+r) / 2;
            if(is_above(relevant_nodes[mid], u)) {
                ans = mid;
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        return (ans != -1 ? relevant_nodes[ans] : -1);
    }

};


vector<int> adjList[MAXN];
int a[MAXN];

vector<int> relevant_nodes[MAXA];
map<int,int> sz[MAXA];
map<int,int> prefix[MAXA];


void dfs_prec(int u, const int mult, int p = -1){
    sz[mult][u] = 1;
    for(auto v: adjListVT[u]){
        if(v == p) continue;

        dfs_prec(v, mult, u);

        sz[mult][u] += sz[mult][v];
    }
}

void dfs_ans(int u, const int mult, int p = -1){
    prefix[mult][u] += prefix[mult][p] + sz[mult][u];
    for(auto v: adjListVT[u]) {
        if(v == p) continue;
        dfs_ans(v, mult, u);
    }
}


int main () {
	//fastIO();
	
	int n, q; cin>>n>>q;
    for(int i = 1; i < n; i++){
        int p; cin>>p; p--;
        adjList[p].push_back(i);
    }

    forn(i, n) cin>>a[i];


    VirtualTreeMaker VTM;
    VTM.build(adjList, 0);

    vector<vector<int>> id_by_a(MAXA);
    forn(i, n) id_by_a[a[i]].push_back(i);


    vector< vector<int> > multiples(MAXA);
    for(int i = 1; i < MAXA; i++){
        for(int j = i; j < MAXA; j += i){
            for(auto id: id_by_a[j]){
                multiples[i].push_back(id);
            }
        }
    }

    for(int i = 2; i <= 2; i++) {
        auto relevant = VTM.virtual_tree(multiples[i]);
        if(relevant.empty()) continue;
        relevant_nodes[i] = relevant;
        

        dfs_prec(relevant.front(), i);
        dfs_ans(relevant.front(), i);
    }


    while(q--){
        int u, v, x; cin>>u>>v>>x; u--, v--;

        int lca = VTM.get_lca(u, v);

        int pu =   VTM.get_first_active_ancestor(u, relevant_nodes[x]);
        int pv =   VTM.get_first_active_ancestor(v, relevant_nodes[x]);
        int plca = VTM.get_first_active_ancestor(lca, relevant_nodes[x]);

        debugg(pu);
        debugg(pv);
        debugg(plca);

        // lli a_pu  =   (pu != -1 ? prefix[x][pu] : 0);
        // lli a_pv  =   (pv != -1 ? prefix[x][pv] : 0);
        // lli a_plca  = (plca != -1 ? prefix[x][plca] : 0);
        // lli sz_plca = (plca != -1 ? sz[x][plca] : 0);

        // debugg(a_pu);
        // debugg(a_pv);
        // debugg(a_plca);
        // debugg(sz_plca);

    }




	return 0;
}

