#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

typedef pair<lli,lli> pairr;

#define pb push_back


typedef long long num_t;
const num_t oo = (num_t) 2e18;
struct func_t {
    num_t a, b;
    func_t(num_t a = 0, num_t b = oo) : a(a), b(b) {}
    num_t query(num_t x) {return a * x + b;}
};
struct node_t {
    node_t *l, *r;
    func_t f;
    node_t(node_t* l = 0, node_t* r = 0, func_t f = func_t()) : l(l), r(r), f(f) {}
    num_t query(num_t x) {return f.query(x);}
};
node_t* upd(node_t* p, int l, int r, int L, int R, func_t f) {
    if (l > R || r < L) return p;
    int M = L + ((R - L) >> 1);
    node_t* res = p ? new node_t(p->l, p->r, p->f) : new node_t();
    if (l <= L && r >= R) {
        int fl = f.query(L) >= (p ? p->query(L) : oo);
        int fr = f.query(R) >= (p ? p->query(R) : oo);
        if (fl && fr) return res;
        if (!fl && !fr) {
            res->f = f;
            return res;
        }
        int fm1 = f.query(M) >= (p ? p->query(M) : oo);
        if (fl && fm1) {
            res->r = upd(res->r, l, r, M + 1, R, f);
            return res;
        }
        if (!fl && !fm1) {
            res->r = upd(res->r, l, r, M + 1, R, res->f);
            res->f = f;
            return res;
        }
        int fm2 = f.query(M + 1) >= (p ? p->query(M + 1) : oo);
        if (fm2 && fr) {
            res->l = upd(res->l, l, r, L, M, f);
            return res;
        }
        if (!fm2 && !fr) {
            res->l = upd(res->l, l, r, L, M, res->f);
            res->f = f;
            return res;
        }
        assert(0);
    }
    res->l = upd(res->l, l, r, L, M, f);
    res->r = upd(res->r, l, r, M + 1, R, f);
    return res;
}
node_t* upd(node_t* p, int l, int r, int L, int R, num_t a, num_t b) {
    return upd(p, l, r, L, R, func_t(a, b));
}
num_t query(node_t* p, int i, int L, int R) {
    if (!p) return oo;
    if (i < L || i > R) return oo;
    num_t res = p->query(i);
    if (L < R) {
        res = min(res, query(p->l, i, L, (L + R) >> 1));
        res = min(res, query(p->r, i, ((L + R) >> 1) + 1, R));
    }
    return res;
}

const int maxN = 1e5+1000;

vector<lli> start(maxN), vel(maxN), prefix(maxN), parent(maxN);
vector< vector< pairr > > adjList(maxN);
vector< node_t *> li_chaos(maxN);

void dfs_prec(int u, int p = -1){
    for(auto [v, w]: adjList[u]){
        if(v == p) continue;
        prefix[v] = prefix[u] + w;
        parent[v] = u;
        dfs_prec(v, u);
    }
}

int n;
lli dp[maxN];

lli L = -1e9, R = 1e9;

void dfs_dp(int u, int p = -1){
    if(u == 1) {
        li_chaos[u] = NULL;
    } else {
        node_t *parent_node = li_chaos[p];

        lli aux = query(parent_node, -vel[u], L, R);
        lli ans = start[u] + prefix[u]*vel[u] + min(0LL, aux);
        dp[u] = ans;


        li_chaos[u] = upd(parent_node, L, R, L, R, prefix[u], dp[u]);
    }

    for(auto [v, w]: adjList[u]){
        if(v == p) continue;
        dfs_dp(v, u);
    }
}



int main () {
	fastIO();
    cin>>n;


    for(int i = 0; i < n-1; i++){
        int u, v, w; cin>>u>>v>>w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    for(int i = 2; i <= n; i++){
        cin>>start[i]>>vel[i];
    }

    dfs_prec(1);
    dfs_dp(1, 0);

    for(int i = 2; i <= n; i++) cout << dp[i] << " ";

	return 0;
}

