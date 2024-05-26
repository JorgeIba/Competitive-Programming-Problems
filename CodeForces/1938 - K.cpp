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

struct Node{
    Node *L = NULL, *R = NULL;
    
    int l, r;
    lli cnt;

    Node() {}
    Node(int l, int r, int cnt = 0): l(l), r(r), cnt(cnt) {}
};

struct PST {

    static Node* build(int l, int r){
        if(l == r) {
            return new Node(l, r);
        } else {
            Node *curr = new Node(l, r);
            int mid = (l+r) / 2;
            curr->L = build(l, mid);
            curr->R = build(mid+1, r);
            return curr;
        }
    }

    static int query(Node *curr, int ql, int qr) {
        int l = curr->l, r = curr->r;
        if(r < ql || l > qr) return 0;
        if(ql <= l && r <= qr) return curr->cnt;
        return query(curr->L, ql, qr) + query(curr->R, ql, qr);
    }

    static Node *update(Node *curr, int pos, int x) {
        int l = curr->l, r = curr->r;
        lli cnt = curr->cnt;
        
        if(pos < l || r < pos) return curr;

        if(l == r) {
            return new Node(l, r, cnt + x);
        }

        Node *node = new Node(l, r);
        node->L = update(curr->L, pos, x);
        node->R = update(curr->R, pos, x);

        node->cnt = node->L->cnt + node->R->cnt;


        return node;
    }

    static int lower_bound(Node *curr, int k) {
        int l = curr->l, r = curr->r;
        if(l == r) return l;
        
        if(k <= curr->L->cnt) {
            return lower_bound(curr->L, k);
        } else {
            return lower_bound(curr->R, k - curr->L->cnt);
        }
    }


    static int kth(Node *curr_R, Node *curr_L, int k) {
        int l = curr_L->l, r = curr_L->r;
        if(l == r) return l;

        lli left = curr_R->L->cnt - curr_L->L->cnt;
        if(k <= left) {
            return kth(curr_R->L, curr_L->L, k);
        } else {
            return kth(curr_R->R, curr_L->R, k - left);
        }
    }

    
};

const int MAXN = 1e5 + 100;
const int MAXLOG = 19;

vector<int> adjList[MAXN];
int ancestors[MAXN][MAXLOG];
int sz[MAXN];
int level[MAXN];


Node *root_1[MAXN]; // To find LCA
Node *root_2[MAXN]; // to find Y
vector<int> S[MAXN];


int get_kth(int u, int k) {
    int v = u;
    for(int i = 0; i < MAXLOG; i++) {
        if(k & (1 << i)) {
            v = ancestors[v][i];
        }
    }
    return v;
}


void dfs_1(int u) {
    for(int i = 1; i < MAXLOG; i++) {
        ancestors[u][i] = ancestors[ancestors[u][i-1]][i-1];
    }

    sz[u] = 1;
    for(auto v: adjList[u]) {
        ancestors[v][0] = u;
        level[v] = level[u] + 1;

        dfs_1(v);

        sz[u] += sz[v];
    }
}


Node *principal;

// Precalculare root_1
void dfs_2(int u, Node *r_1_p) {
    root_1[u] = PST::update(r_1_p, u, sz[u]);

    for(auto v: adjList[u]) {
        Node *root_1_v = PST::update(root_1[u], u, -sz[v]);
        dfs_2(v, root_1_v);
    }
}

// Precalcualte root_2
void dfs_3(int u) {
    root_2[u] = PST::update(principal, u, 1);
    S[u].push_back(u);

    for(auto v: adjList[u]) {
        dfs_3(v);
        
        if(SZ(S[u]) < SZ(S[v])) {
            swap(S[u], S[v]);
            root_2[u] = root_2[v];
        }

        for(auto x: S[v]) {
            S[u].push_back(x);
            root_2[u] = PST::update(root_2[u], x, 1);
        }
    }
}



int main () {
	fastIO();

    int n, q; cin>>n>>q;

    int root = 0;
    forn(i, n) {
        int p; cin>>p; p--;
        if(p == -1) {
            root = i;
            continue;
        }
        adjList[p].push_back(i);
    }

    ancestors[root][0] = root;
    dfs_1(root);

    principal = PST::build(0, n-1);
    dfs_2(root, principal);

    dfs_3(root);

    // for(int i = 0; i < n; i++) {
    //     cout << i << " ST -> " << endl;
    //     for(int j = 0; j < n; j++) {
    //         cout << PST::query(root_2[i], j, j) << " ";
    //     }
    //     cout << endl;
    // }


    forn(_, q) {
        lli k; cin>>k; k--;

        int x = k / n;
        int lca, y;
        k -= x * n;

        lca = PST::lower_bound(root_1[x], k+1);

        k++;
        // debugg(k);
        // debugg(PST::query(root_1[x], 0, lca) - PST::query(root_1[x], lca, lca));
        k = k - (PST::query(root_1[x], 0, lca) - PST::query(root_1[x], lca, lca));
        // cout << x << " --- " << lca << " -- " << k << endl;


        if(x == lca) {
            y = PST::kth(root_2[x], principal, k);
        } else {
            int p_low = get_kth(x, level[x] - level[lca] - 1);
            // debugg(p_low);
            y = PST::kth(root_2[lca], root_2[p_low], k);
        }

        lli ans = 1LL * x * n * n + 1LL * lca * n + y;
        cout << ans << endl;
    }


	return 0;
}

