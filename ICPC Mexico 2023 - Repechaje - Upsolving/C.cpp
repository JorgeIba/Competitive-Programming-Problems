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

const int MAXN = 1e5 + 10;
const int INF = 2e9;

int v[MAXN];
int ans[MAXN];
vector<int> adjList[MAXN];

void dfs(int u, int p, vector<int> &increasing) {
    if(p != -1) {
        ans[u] = ans[p];
    }

    auto idx = upper_bound(all(increasing), v[u] - 1) - begin(increasing);
    ans[u] = max(ans[u], (int)idx+1);

    int exchange = -1;
    if(v[u] < increasing[idx]) {
        exchange = increasing[idx];
        increasing[idx] = v[u];
    }
    
    for(auto v: adjList[u]) {
        dfs(v, u, increasing);
    }

    if(exchange != -1) {
        // Rollback
        increasing[idx] = exchange;
    }
}

int main () {
    fastIO();
    
    int n; cin>>n;

    for(int i = 1; i < n; i++) {
        int p; cin>>p; p--;
        adjList[p].push_back(i);
    }

    for(int i = 0; i < n; i++)
        cin>>v[i];
    

    vector<int> increasing(n+2, INF);
    dfs(0, -1, increasing);

    for(int i = 1; i < n; i++) {
        cout << ans[i] << " ";
    }

	return 0;
}

