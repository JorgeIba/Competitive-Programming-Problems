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

const int MAXN = 1e5+100;
const int MOD = 1e9+7;

vector< pair<int,lli> > adjList[MAXN];
lli pref_xor[MAXN];
int Time = 1;
int disc[MAXN];
vector<lli> cycle_xor;
vector<int> visited;
const int LOG_D = 64;
vector<lli> basis(LOG_D);
vector<lli> val_basis;

lli dp[LOG_D][LOG_D][2];

void dfs(int u, int p = -1) {
    disc[u] = Time++;
    visited.push_back(u);

    for(auto [v, w]: adjList[u]) {
        if(v == p) continue;
        
        if(!disc[v]){
            pref_xor[v] = pref_xor[u] ^ w;
            
            dfs(v, u);
        } else {
            if(disc[v] < disc[u]) {
                lli path_xor = pref_xor[v] ^ pref_xor[u] ^ w;
                cycle_xor.push_back(path_xor);
            }
        }
    }
}

void insert_vector(lli mask, bool zeros = false) {
    for(int i = LOG_D-1; i>=0; i--){
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i]){
            basis[i] = mask;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++){
				if(j==i) continue;
				if(j < i){
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
				}
				else{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
				}
			}
            return;
        }
        mask ^= basis[i];
    }
}
 
lli f(int bit, int idx, int flag){
    if(idx == SZ(val_basis)) {
        if(flag) return (1LL << bit) % MOD;
        return 0;
    }
 
    lli &ans = dp[bit][idx][flag];
    if(ans != -1) return ans;
 
    bool bit_basis = val_basis[idx] & (1LL << bit);
 
    lli yes = f(bit, idx+1, flag ^ (bit_basis));
    lli no = f(bit, idx+1, flag);
    return ans = (yes + no) % MOD;
}



lli totalAns = 0;

void calc_component(int root) {
    Time = 1;
    cycle_xor.clear();
    visited.clear();
    fill(all(basis), 0);
    val_basis.clear();
    memset(dp, -1, sizeof(dp));

    dfs(root);

    for(auto x: cycle_xor) {
        insert_vector(x);
    }

    for(int i = 0; i < LOG_D; i++){
        if(basis[i]) {
            val_basis.push_back(basis[i]);
        }
    }

    int m = SZ(visited);

    sort(all(visited));
    vector< array<int, LOG_D> > prefix(m);
    forn(i, LOG_D) prefix[0][i] = 0;


    assert(pref_xor[visited[0]] == 0);
    for(int i = 1; i < m; i++){
        // int u = visited[i];

        prefix[i] = prefix[i-1];
        for(int j = 0; j < LOG_D; j++) {
            prefix[i][j] += (bool)(pref_xor[visited[i-1]] & (1LL << j));
        }
    }

    lli ans = 0;

    for(int i = 0; i < m; i++){
        int u = visited[i];
        for(int j = 0; j < LOG_D; j++){
            lli on = prefix[i][j];
            lli off = i - on;

            if(pref_xor[u] & (1LL << j)) {
                swap(on, off);
            }

            lli yes = on * f(j, 0, 1) % MOD;
            lli no = off * f(j, 0, 0) % MOD;

            ans = (ans + yes + no) % MOD;
        }
    }
    totalAns = (totalAns + ans) % MOD;
}



int main () {
	fastIO();

    int n, m; cin>>n>>m;
    
    forn(i, m) {
        int u, v;
        lli w; cin>>u>>v>>w; u--, v--;
        
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }
    
    forn(i, n){
        if(!disc[i]){
            calc_component(i);
        }
    }

    cout << totalAns << endl;

	return 0;
}

