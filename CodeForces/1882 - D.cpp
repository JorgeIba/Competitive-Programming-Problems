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


const int MAXN = 2e5 + 100;
const int MAXLOG = 20;

vector<int> adjList[MAXN];
lli xors[MAXN];
lli dp[MAXN];
lli sz[MAXN];

void dfs_prec(int u, int parent = -1){
    sz[u] = 1;
    for(auto v: adjList[u]){
        if(v == parent) continue;
        dfs_prec(v, u);

        sz[u] += sz[v];
    }
}


void dfs(int u, int p = -1){
    lli cost = 0;
    if(p != -1) {
        cost += (xors[u] ^ xors[p]) * sz[u];
    }

    for(auto v: adjList[u]){
        if(v == p) continue;

        dfs(v, u);
        cost += dp[v];   
    }

    dp[u] = cost;
}

lli ans[MAXN];
void dfs_ans(int u, lli ans_p, int sz_p = 0, int p = -1) {

    lli new_dp = dp[u];
    if(p != -1) {
        new_dp -= (xors[u] ^ xors[p]) * sz[u];
        new_dp += ans_p;
    }

    ans[u] = new_dp;
    for(auto v: adjList[u]){
        if(v == p) continue;

        int sz_me = sz[u] - sz[v] + sz_p;
        lli new_dp_p = ans[u] - dp[v] + (xors[v] ^ xors[u]) * sz_me;
    
        dfs_ans(v, new_dp_p, sz_me, u);
    }
}

void main_(){
	int n; cin>>n;

    forn(i, n) cin>>xors[i];

    forn(i, n){
        adjList[i].clear();
    }

    forn(i,n-1){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int root = 0;
    dfs_prec(root);
    dfs(root);
    dfs_ans(root, 0);

    forn(i, n) cout << ans[i] << " ";
    cout << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}


