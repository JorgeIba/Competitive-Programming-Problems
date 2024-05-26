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


const int MAXN = 2e5 + 100;

vector<int> adjList[MAXN];


int depth[MAXN];

void dfs_prec(int u, int p = -1){
    for(auto v: adjList[u]){
        if(v == p) continue;
        depth[v] = depth[u]+1;
        dfs_prec(v, u);
    }
}


int dir[MAXN];
bool dfs_dir(int u, int target, int p = -1){
    if(u == target) return true;

    for(auto v: adjList[u]){
        if(v == p) continue;
        if(dfs_dir(v, target, u)){
            dir[u] = v;
            return true;
        }
    }
    return false;
}


int ans[MAXN];
int Time = 1;
void dfs_ans(int u, int p = -1){
    ans[u] = Time++;
    for(auto v: adjList[u]){
        if(v == p || v == dir[u]) continue;
        dfs_ans(v, u);
    }

    if(dir[u] != -1)
        dfs_ans(dir[u], u);

    Time++;
}


int main () {
	//fastIO();
    int n; cin>>n;

    forn(i, n-1) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    auto get_root = [&](){
        queue<int> q;
        vector<int> dist(n, -1);

        dist[0] = 0;
        q.push(0);

        while(!q.empty()){
            auto u = q.front(); q.pop();

            for(auto v: adjList[u]){
                if(dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        int root = max_element(all(dist)) - dist.begin();
        return root;
    };

    int root = get_root();
    dfs_prec(root);
    int last = max_element(depth, depth+n) - depth;


    // debugg(root);
    // debugg(last);

    memset(dir, -1, sizeof(dir));
    dfs_dir(root, last);

    dfs_ans(root);

    forn(i, n){
        cout << ans[i] << " ";
    }
    cout << endl;


	return 0;
}

