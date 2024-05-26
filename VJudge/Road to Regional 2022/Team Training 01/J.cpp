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

#define ll __int128

struct LCA_T{
    const static int maxLOG = 19;
    int n;
    vector<int> depth, order;    
    vector< vector<int> > ancestors;

    template<class G>
    LCA_T(int n, const G &adjList, int root = 1): n(n), depth(n) {
        ancestors.assign(n, vector<int>(maxLOG));
        for(int i = 0; i < n; i++) ancestors[i][0] = i;

        dfs(root, adjList, 0);
        prec();
    }


    template<class G>
    void dfs(int u, const G &adjList, int p = -1) {
    
        order.push_back(u);
        for(auto v: adjList[u]){
            if(v == p) continue;

            ancestors[v][0] = u;
            depth[v] = depth[u] + 1;

            dfs(v, adjList, u);
        }
    }

    void prec() {
        for(auto u: order) 
            for(int i = 1; i < maxLOG; i++) 
                ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
        order.clear();
    }

    int get_kth_parent(int u, int k){
        for(int i = maxLOG - 1; i >= 0; i--) 
            if(k & (1 << i))
                u = ancestors[u][i];

        return u;
    }

    int get_lca(int u, int v) {
        if(depth[u] > depth[v]) swap(u, v);
        v = get_kth_parent(v, depth[v] - depth[u]);

        for(int i = maxLOG-1; i >= 0; i--) {
            if(ancestors[u][i] != ancestors[v][i]) {
                u = ancestors[u][i];
                v = ancestors[v][i];
            }
        }
        return u != v ? ancestors[u][0] : u;
    }
};



template<typename T>
struct FenwickTree{
	int n;
    vector< vector<T> > bit;

    FenwickTree(int n): n(n) {
        bit.assign(2, vector<T>(n+10));
    }

	T get(int x, int i) {
		T ret = 0;
		for (; i; i -= i&-i) ret += bit[x][i];
		return ret;
	}
	void add(int x, int i, T val) {
		for (; i <= n; i += i&-i) bit[x][i] += val;
	}
	T get2(int p) {
		return get(0, p) * p + get(1, p);
	}
	T query(int l, int r) {
		return get2(r+1) - get2(l);
	}
	void update(int l, int r, T x) {
		add(0, l+1, x), add(0, r+2, -x);
		add(1, l+1, -x*l), add(1, r+2, x*(r+1));
	}
};


const int MAXN = 3e5+100;

vector<int> adjList[MAXN];
int depth[MAXN], parent[MAXN];

FenwickTree<ll> *cnst = new FenwickTree<ll>(MAXN);
FenwickTree<ll> *lin  = new FenwickTree<ll>(MAXN);
FenwickTree<ll> *quad = new FenwickTree<ll>(MAXN);


void prec(int u, int p) {
    parent[u] = p;

    for(auto v: adjList[u]) {
        if(v == p) continue;

        depth[v] = depth[u] + 1;
        prec(v, u);
    }
}


array<int,2> rangess[MAXN];
vector<int> order;
int timee = 0;

void dfs_euler(int u, int p = -1) {
    order.push_back(u);
    rangess[u][0] = timee++;

    for(auto v: adjList[u]) {
        if(v == p) continue;

        dfs_euler(v, u);
    }

    rangess[u][1] = timee-1;
}


ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}


int main () {
	fastIO();

    int n; cin>>n;

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    prec(0, 0);
    dfs_euler(0);


    LCA_T *LCA = new LCA_T(n, adjList, 0);


    auto update = [&](int l, int r, int u, lli c, lli k){
        auto du = depth[u];
        ll quad_c = k;
        ll lin_c  = k*(1 - 2*du) + 2*c;
        ll cnst_c = k * du * (du - 1) + 2*c*(1 - du);

        quad->update(l, r, quad_c);
        lin->update(l, r, lin_c);
        cnst->update(l, r, cnst_c);
    };

    auto sum = [&](int u) {
        int pos = rangess[u][0];
        ll quad_c = quad->query(pos, pos);
        ll lin_c  = lin->query(pos, pos);
        ll cnst_c = cnst->query(pos, pos);
        int du = depth[u];

        return quad_c*du*du + lin_c*du + cnst_c; 
    };

    auto query = [&](int u, int v) {
        auto lca = LCA->get_lca(u, v);
        ll ans = sum(u) + sum(v) - sum(lca);
        if(lca != 0)
            ans -= sum( parent[lca] );
        return ans;
    };


    int q; cin>>q;

    while(q--) {
        int t; cin>>t;
        if(t == 0) {
            int u, v; cin>>u>>v; u--, v--;

            ll ans = query(u, v) / 2;
            cout << ans << endl;

        } else {
            int u, c, k; cin>>u>>c>>k; u--;

            update(rangess[u][0], rangess[u][1], u, c, k);
        }
    }



	return 0;
}

