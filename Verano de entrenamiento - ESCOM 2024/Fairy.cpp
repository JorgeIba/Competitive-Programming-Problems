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


const int MAXN = 1e4 + 100;

vector<int> adjList[MAXN];
bool visited[MAXN];

int Time = 1;
int disc[MAXN];

// set< pair<int,int> > contrs;
int total_contrs = 0;

int colors[MAXN];
const int BLUE = 0, RED = 1;

int prefix_cntr[MAXN];
int prefix_ok[MAXN];

int cntr_passing[MAXN];
int ok_passing[MAXN];

void dfs_prec(int u, int color = BLUE, int p = -1){
    colors[u] = color;
    disc[u] = Time++;
    for(auto v: adjList[u]){
        if(v == p) continue;
        if(disc[v] == 0) {
            dfs_prec(v, !color, u);
        } else if(disc[v] < disc[u]) { // backedge
            if(colors[u] == colors[v]) { // contradiction
                prefix_cntr[v]--;
                prefix_cntr[u]++;
                total_contrs++;
            } else {
                prefix_ok[v]--;
                prefix_ok[u]++;
            }
        }
    }
}

int dfs_sum_cntr(int u, int p = -1){
    visited[u] = true; 
    int val = prefix_cntr[u];
    for(auto v: adjList[u]) {
        if(v == p) continue;
        if(visited[v]) continue; // backedge or descendent already visited
        val += dfs_sum_cntr(v, u);
    }

    return cntr_passing[u] = val;
}

int dfs_sum_ok(int u, int p = -1){
    visited[u] = true;
    int val = prefix_ok[u];
    for(auto v: adjList[u]) {
        if(v == p) continue;
        if(visited[v]) continue;
        val += dfs_sum_ok(v, u);
    }

    return ok_passing[u] = val;
}


map< pair<int,int>, int > edge_to_idx;
vector<int> ans;


void dfs_ans_back(int u, int p = -1) {
    visited[u] = true;
    for(auto v: adjList[u]){
        if(v == p) continue;
        if(disc[v] < disc[u]) {
            if(colors[v] == colors[u]){
                if(total_contrs == 1) {
                    pair<int,int> edge = {min(u,v), max(u,v)};
                    ans.push_back(edge_to_idx[edge]);
                }
            } else {
                if(total_contrs == 0){
                    pair<int,int> edge = {min(u,v), max(u,v)};
                    ans.push_back(edge_to_idx[edge]);
                }
            }
        }
    }

    for(auto v: adjList[u]){
        if(v == p) continue;
        if(visited[v]) continue;
        
        dfs_ans_back(v, u);
    }
}

void dfs_ans_tree(int u, int p = -1){
    if(p != -1) {
        if(cntr_passing[u] and ok_passing[u]) { // No se puede eliminar

        } else {
            int solving = cntr_passing[u];
            if(solving == total_contrs) {
                pair<int,int> edge = {min(u,p), max(u,p)};
                ans.push_back(edge_to_idx[edge]);
            }
        }
    }
    // debugg(u);

    visited[u] = true;
    for(auto v: adjList[u]){
        if(v == p) continue;
        if(visited[v]) continue;
        dfs_ans_tree(v, u);
    }
}

int main () {
	// fastIO();

	int n, m; cin>>n>>m;
    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edge_to_idx[{min(u,v), max(u,v)}] = i;
    }

    vector<bool> roots(n);
    forn(i, n){
        if(disc[i]) continue;
        roots[i] = 1;
        dfs_prec(i);

        fill(visited, visited+n, false);
        dfs_sum_cntr(i);

        fill(visited, visited+n, false);
        dfs_sum_ok(i);
    }

    forn(i, n){
        if(roots[i]) {
            fill(visited, visited+n, false);
            dfs_ans_back(i);
            
            fill(visited, visited+n, false);
            dfs_ans_tree(i);
        }
    }

    sort(all(ans));
    cout << SZ(ans) << endl;
    for(auto idx: ans) {
        cout << idx+1 << " ";
    }
    cout << endl;

    



	return 0;
}

