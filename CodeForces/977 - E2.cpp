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

const lli INF = 1e15;

struct DSU {
    int n;
    vector<int> parent, sz;
    vector< multiset<lli> > dp;
    vector< lli > total_sum;
    vector<int> cnt;

    DSU(int n): n(n), parent(n), sz(n, 1), dp(n, {0}), total_sum(n), cnt(n) {
        iota(all(parent), 0);
    }

    int root(int u) {
        return parent[u] = (parent[u] == u ? u : root(parent[u]));
    }

    bool join(int u, int v, lli w) {
        u = root(u), v = root(v);
        if(u == v) return false;
        if(sz[u] < sz[v])
            swap(u, v);



        auto &dp_1 = dp[u];
        auto &dp_2 = dp[v];

        lli best_opt = min(cnt[v] * w - total_sum[v], cnt[u] * w - total_sum[u]);
        dp_1.insert(best_opt);
        total_sum[u] += best_opt;

        for(auto x: dp_2) {
            dp_1.insert(x);
            total_sum[u] += x;
        }
            
        total_sum[u] -= *dp_1.begin();
        dp_1.extract(*dp_1.begin());


        parent[v] = u;
        sz[u] += sz[v];
        cnt[u] += cnt[v];


        return true;
    }
};

void main_() {
    int n, m, p; cin>>n>>m>>p;
    vector<int> S(p);
    for(auto &s: S) {
        cin>>s;
        s--;
    }

    vector< tuple<int,int,int> > edges(m);
    for(auto &[w, u, v]: edges) {
        cin>>u>>v>>w;
        u--, v--;
    }

    vector< vector<pair<int,int>> > adjList(n);

    DSU D(n);
    for(auto s: S)
        D.cnt[s] = 1;

    sort(all(edges));
    for(auto [w, u, v]: edges) {
        if(D.root(u) == D.root(v)) continue;

        D.join(u, v, w);
    }

    vector<lli> ans;
    lli acum = 0;

    int root = D.root(0);
    for(auto x: D.dp[root]) {
        acum += x;
        ans.push_back(acum);
    }
    
    reverse(all(ans));
    for(auto x: ans)
        cout << x << " ";
    cout << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}
