#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;



lli binPow(lli a, lli b, lli mod){
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


vector<vector<lli>> adjList;

vector<lli> hashed;

const lli p1 = 37, p2 = 31, p3 = 19, MOD = 1e9+7;


map<lli,lli> diff;
lli ans = 1e18, ans_u = 1;
lli n; 

void insert(lli hash_u) {
    diff[hash_u]++;
}

void dec(lli hash_u) {
    diff[hash_u]--;
    if(!diff[hash_u]) diff.erase(hash_u);
}


void dfs(int u, int p) {
    lli hash_u = 1;
    for(auto v: adjList[u]) {
        if(v == p) continue;

        dfs(v, u);
        hash_u = hash_u * (p3 - hashed[v] + MOD) % MOD;
    }

    hashed[u] = p1 * hash_u % MOD * p2 % MOD;
    insert(hashed[u]);
}


void solve(int u, int p) {

    lli ansTemp = n - SZ(diff) + 1;

    if(ansTemp < ans) {
        ans = ansTemp;
        ans_u = u;
    }

    for(auto v: adjList[u]) {
        if(v == p) continue;

        dec(hashed[u]);
        hashed[u] = hashed[u] * binPow(p3 - hashed[v] + MOD, MOD-2, MOD) % MOD;
        insert(hashed[u]);


        dec(hashed[v]);
        hashed[v] = hashed[v] * (p3 - hashed[u] + MOD) % MOD;
        insert(hashed[v]);

        solve(v, u);

        dec(hashed[v]);
        hashed[v] = hashed[v] * binPow(p3 - hashed[u] + MOD, MOD-2, MOD) % MOD;
        insert(hashed[v]);


        dec(hashed[u]);
        hashed[u] = hashed[u] * (p3 - hashed[v] + MOD) % MOD;
        insert(hashed[u]);
    }
}

int main () {
	//fastIO();

    cin>>n;
    adjList.resize(n+1);
    hashed.resize(n+1);
    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    dfs(1, -1);

    solve(1, -1);

    cout << ans_u << endl;

	return 0;
}

