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

const int WILD = 0, ONE = 1, ZERO = 2;
struct DSU{
    int n;
    vector<int> parent, sz;
    vector<int> color;
    bool is_valid = true;
    
    DSU(int n): n(n), parent(n), sz(n, 1), color(n, WILD) {
        iota(all(parent), 0);
    }

    int root(int u) {
        return parent[u] = parent[u] == u ? u : root(parent[u]);
    }

    void set_color(int u, int v) {
        u = root(u);
        if(v == 0)
            color[u] |= ZERO;
        else if(v == 1)
            color[u] |= ONE;
        
        if(color[u] == 3)
            is_valid = false;
    }

    void join(int u, int v) {
        u = root(u), v = root(v);
        if(u == v)
            return;

        if(sz[u] < sz[v])
            swap(u, v);
        
        parent[v] = u;
        sz[u] += sz[v];
        color[u] |= color[v];
        if(color[u] == 3)
            is_valid = false;
    }
};

const int MOD = 1e9 + 7;


void main_() {
    int n, m, k, q; cin>>n>>m>>k>>q;

    vector< tuple<int,int, int> > values(k);
    int V = -1;
    for(auto &[i, j, v]: values) {
        cin>>i>>j>>v;
        i--, j--;
        if(i == 0 && j == 0)
            V = v;
    }
    
    auto get_ans_per_bit = [&](int bit, int val_0) -> int { 
        if(V != -1) {
            if(((V >> bit) & 1) != val_0) 
                return 0;
        }

        DSU D(n + m - 1);
        D.set_color(0, val_0);
        for(auto [i, j, v]: values) {
            v = (v >> bit) & 1;

            if(i == 0) {
                D.set_color(j, v);
            } else if(j == 0) {
                D.set_color(m + i - 1, v);
            } else {
                int val = val_0 ^ v;
                if(!val) {
                    D.join(j, m + i - 1);
                }
            }

            if(!D.is_valid)
                return 0;
        }

        vector< vector<int> > adjList(n + m - 1);
        for(auto [i, j, v]: values) {
            v = (v >> bit) & 1;
            
            if(i == 0 || j == 0) continue;

            int val = val_0 ^ v;
            if(val) {
                int node_u = D.root(m + i - 1), node_v = D.root(j);
                adjList[node_u].push_back(node_v);
                adjList[node_v].push_back(node_u);
            }

            if(!D.is_valid) {
                return 0;
            }
        }



        vector<int> color(n + m - 1, -1);
        auto bfs = [&](queue<int> &q) -> bool {
            while(!q.empty()) {
                auto u = q.front(); q.pop();
                for(auto v: adjList[u]) {
                    if(color[v] != -1) {
                        if(color[u] == color[v]) return false;
                        continue;
                    }

                    color[v] = color[u] ^ 1;
                    q.push(v);
                }
            }
            return true;
        };

        vector<int> colored;
        queue<int> q;
        for(int i = 1; i < n + m - 1; i++) {
            int u = D.root(i);
            if(i != u) continue;
            if(D.color[u] == 0) continue;

            assert(color[u] != 3);

            color[u] = (D.color[u] == ZERO ? 0 : 1);
            
            q.push(u);
        }

        if(!bfs(q)) {
            return 0;
        }

        int ans = 1;
        for(int i = 1; i < n + m - 1; i++) {
            int u = D.root(i);
            if(i != u) continue;
            if(color[u] != -1) continue;

            color[u] = 0;
            q.push(u);
            if(!bfs(q)) {
                return 0;
            }

            ans = (ans + ans);
            if(ans >= MOD) ans -= MOD;
        }

        return ans;
    };

    int ans = 1;
    for(int i = 0; i < 30; i++) {
        ans = 1LL * ans * (get_ans_per_bit(i, 0) + get_ans_per_bit(i, 1)) % MOD;
    }

    cout << ans << endl;
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

