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


const int MAXN = 1e5 + 10;
const int MAXK = 20 + 1;


vector<int> adjList[MAXN];

int n, k; 
int a[MAXN];
int dist[MAXN][2*MAXK];


void dfs_prec(int u, int p = -1){
    dist[u][0] ^= a[u];

    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_prec(v, u);
        
        for(int i = 0; i < 2*k; i++){
            dist[u][(i+1) % (2*k)] ^= dist[v][i];
        }
    }
}


int ans[MAXN];
void dfs_ans(int u, int p = -1){
    for(int i = k; i < 2*k; i++){
        ans[u] ^= dist[u][i];
    }


    for(auto v: adjList[u]){
        if(v == p) continue;

        // Quitar de U
        for(int i = 0; i < 2*k; i++){
            dist[u][(i+1) % (2*k)] ^= dist[v][i];
        }

        // Agregar a V
        for(int i = 0; i < 2*k; i++){
            dist[v][(i+1) % (2*k)] ^= dist[u][i];
        }

        dfs_ans(v, u);

        // Quitar de V
        for(int i = 0; i < 2*k; i++){
            dist[v][(i+1) % (2*k)] ^= dist[u][i];
        }

        // Agregar a U
        for(int i = 0; i < 2*k; i++){
            dist[u][(i+1) % (2*k)] ^= dist[v][i];
        }
    }
}


int main () {
	fastIO();
    cin>>n>>k;


    forn(i, n-1) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    forn(i, n){
        cin>>a[i];
    }


    dfs_prec(0);
    dfs_ans(0);

	
    for(int i = 0; i < n; i++){
        cout << (ans[i] > 0 ? 1 : 0) << " ";
    }


	return 0;
}

