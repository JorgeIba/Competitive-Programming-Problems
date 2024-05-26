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


lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

int main () {
	//fastIO();
    
    int n, m, k; cin>>n>>m>>k;

    vector< vector<int> > adjList(n);
    forn(i, m) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    vector<int> sizes;
    vector<bool> visited(n);

    auto dfs = [&](const auto &dfs, int u) {
        if(visited[u]) {
            return 0;
        }

        visited[u] = true;
        int sz = 1;
        for(auto v: adjList[u]) {
            sz += dfs(dfs, v);
        }

        return sz;
    };

    forn(i, n) {
        if(visited[i]) continue;
        sizes.push_back(dfs(dfs, i));
    }

    lli ans = 1;
    lli sum = 0;
    lli rhs = 0;
    for(auto sz: sizes) {
        ans = ans * sz % k;
        sum = (sum + sz) % k;
        rhs += (1 - sz);
    }

    // debugg(ans);
    // debugg(sum);
    // debugg(rhs);
    // debugg(n-2+rhs);

    if(SZ(sizes) == 1) {
        cout << 1 % k << endl;
    } else if(n-2 + rhs < 0) {
        cout << 0 << endl;
    } else {
        ans = ans * powerMod(sum, n-2 + rhs, k) % k;

        cout << ans << endl;   
    }


	return 0;
}

