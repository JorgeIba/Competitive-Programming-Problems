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

vector<int> adjList[MAXN];
int val[MAXN];
int pref[MAXN];


void dfs_prec(int u, int pref_p = 0, int p = -1){
    pref[u] = pref_p ^ val[u];
    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_prec(v, pref[u], u);
    }
}


set<int> xor_sub[MAXN];
int ans = 0;
void dfs_ans(int u, int p = -1){

    int greatest = -1;
    for(auto v: adjList[u]){
        if(v == p) continue;

        dfs_ans(v, u);

        if(greatest == -1 || SZ(xor_sub[greatest]) < SZ(xor_sub[v]))
            greatest = v;
    }

    if(greatest != -1)
        swap(xor_sub[u], xor_sub[greatest]);

    bool ok = true;
    for(auto v: adjList[u]){
        if(v == p || v == greatest) continue;
        for(auto pref_vs: xor_sub[v]) {
            if(xor_sub[u].count(pref_vs ^ val[u])) {
                ok = false;
            }
        }

        for(auto pref_vs: xor_sub[v]){ 
            xor_sub[u].insert(pref_vs);
        }
    }

    if(xor_sub[u].count(pref[u] ^ val[u]))
        ok = false;

    if(ok) {
        xor_sub[u].insert(pref[u]);
    } else {
        ans++;
        xor_sub[u].clear();
    }
}


int main () {
	//fastIO();
	
    int n; cin>>n;

    forn(i, n) cin>>val[i];

    forn(i,n-1){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs_prec(0);
    dfs_ans(0);

    cout << ans << endl;




	return 0;
}

