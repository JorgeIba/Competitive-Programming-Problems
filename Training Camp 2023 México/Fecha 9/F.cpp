#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define all(a) a.begin(), a.end()
#define SZ(a) (int)a.size()
#define forn(i, n) for(int i = 0; i < n; i++)
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define endl "\n"

using namespace std;

vector< vector<int> > adjList;
vector<int> child, nxt;

const lli MOD = 1e9+7;

lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

void dfs_prec(int u, int p = -1) {
    bool f = true;
    int before = 0;
    for(auto v: adjList[u]) {
        if(v == p) continue;
        if(f) {
            child[u] = v;
            f = !f;
        } else {
            nxt[before] = v;  
        } 

        dfs_prec(v, u);
        before = v;
    }
}


lli f(int, int, bool);


const int maxN = 2e5+100;
lli dp_g[maxN][3][3];
lli dp_f[maxN][3][2];

lli g(int u, int k, int joins) {
    if(u == -1) return k == 0;

    lli &ans= dp_g[u][k][joins];
    if(ans != -1) return ans;
    ans = 0;
    

    // Los que nos vamos a rifar mi subarbol
    for(int i = 0; i <= k; i++){
        if(joins){
            ans += f(u, i, true) * g(nxt[u], k - i, joins - 1) % MOD;
            ans += f(u, i, false) * g(nxt[u], k - i, joins) % MOD;
        } else {
            ans += f(u, i, false) * g(nxt[u], k - i, 0) % MOD;
        }
        if(ans >= MOD) ans -= MOD;
    }


    return ans;
}

lli f(int u, int k, bool will_join) {

    lli &ans= dp_f[u][k][will_join];
    if(ans != -1) return ans;
    ans = 0;

    if(will_join) {
        // ME TOMO
        // ME UNO CON MI PAPA Y QUE MIS HIJOS SE RIFEN LOS QUE FALTAN
        (ans += g(child[u], k, 1)) %= MOD;    
    } else {
        // NO ME TOMO, QUE MIS HIJOS SE RIFEN LOS QUE FALTAN
        (ans += g(child[u], k, 0)) %= MOD;

        // EMPIEZO UN NUEVO CAMINO
        if(k)
            (ans += g(child[u], k-1, 2)) %= MOD;
    }
    
    

    return ans % MOD;
}





void solve() {
    int n; cin>>n;

    adjList.clear();
    child.clear();
    nxt.clear();
    
    adjList.resize(n);
    child.resize(n, -1);
    nxt.resize(n, -1);

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs_prec(0);

    for(int i = 0; i < n; i++) {
        memset(dp_f[i], -1, sizeof(dp_f[i]));
        memset(dp_g[i], -1, sizeof(dp_g[i]));
    }

    lli ans = f(0, 2, false);

    cout << ans << endl;
}




int main(){
    fastIO();
    int t; cin>>t;

    while(t--) solve();

    return 0;
}