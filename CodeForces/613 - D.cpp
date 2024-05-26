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

    int virtual_tree(vector<int> nodes){
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

        return nodes.front();
    }
};




vector<int> adjList[MAXN];
bool important[MAXN];

int ans = 0;
bool is_ans = true;
int solve(int u, int p = -1){

    int cnt_child = 0;
    for(auto v: adjListVT[u]){
        if(v == p) continue;
        if(important[u] && important[v] && depth[v] - depth[u] == 1) {
            is_ans = false;
        }

        cnt_child += solve(v, u);
    }
    
    if(important[u]) {
        ans += cnt_child;
        return 1;
    } else {
        if(cnt_child > 1){
            ans++;
            return 0;
        } else return cnt_child;
    }
}


int main () {
	fastIO();

    int n; cin>>n;
    
    forn(i, n-1){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    VirtualTreeMaker VTM;
    VTM.build(adjList, 0);

    int q; cin>>q;
    while(q--){
        int k; cin>>k;
        vector<int> nodes(k);
        for(auto &x: nodes) cin>>x;
        for(auto &x: nodes) x--, important[x] = true;


        int root_vt = VTM.virtual_tree(nodes);

        solve(root_vt);         
        cout << (is_ans ?  ans : -1) << endl;

        ans = 0;
        is_ans = true;
        for(auto x: nodes) important[x] = false;
    }



	return 0;
}

