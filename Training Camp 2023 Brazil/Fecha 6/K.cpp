#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


const int maxN = 1e5 + 100;
const int maxLOG = 20;

vector< vector<int> > adjList;
vector<int> depth, order;
int ancestors[maxN][maxLOG];


void dfs_prec(int u, int depth_u=0, int p = -1) {
    ancestors[u][0] = (p != -1 ? p : u);

    depth[u] = depth_u;
    order.push_back(u);

    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_prec(v, depth_u+1, u);
    }
}

void prec() {
    for(auto u: order) {
        for(int i = 1; i < maxLOG && (1<<i) <= depth[u]; i++) {
            ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
        }
    }
}

int get_kth_parent(int u, int k){
    for(int i = maxLOG - 1; i >= 0; i--) {
        if(k & (1 << i)) {
            u = ancestors[u][i];
        }
    }
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




template<typename T>
struct SegTreePers {
    const static T neutro = 0; // Neutro of operation
    struct Node{
        int l, r;
        T sum;
        Node *left = NULL, *right = NULL;

        Node(int l, int r, T val = neutro): l(l), r(r), sum(val) {}

        void extend(){
            int mid = l + ((r - l) >> 1);
            if(!left) {
                left = new Node(l, mid);
                right = new Node(mid+1, r);
            }
        }
    };

    int lMax, rMax;
    vector<Node*> versions;

    SegTreePers(int lMax, int rMax): lMax(lMax), rMax(rMax) {
        versions.push_back(new Node(lMax, rMax));
    }

    // Operation
    T merge(T vleft, T vright) { 
        return vleft + vright;
    }

    // Recursive Calls
    Node* updateVal(int pos, Node* curr, T val) {   
        int l = curr->l, r = curr->r;
        int val_before = curr->sum;

        if(pos < l || r < pos) return curr;
        if( l == r ) {
            return new Node(l, r, val_before + val);
        }
        
        curr->extend();

        Node *newNode = new Node(l, r);
        newNode->left = updateVal(pos, curr->left, val);
        newNode->right = updateVal(pos, curr->right, val);
        newNode->sum = merge(newNode->left->sum, newNode->right->sum);
        
        return newNode;
    }

    T queryKthSmallest(Node* curr_l, Node* curr_r, int k) {
        int l = curr_r->l, r = curr_r->r;
        if(l == r) return l;

        T left_sum = curr_r->left->sum - curr_l->left->sum;

        if(k > left_sum)
            return queryKthSmallest(curr_l->right, curr_r->right, k - left_sum);
        else 
            return queryKthSmallest(curr_l->left, curr_r->left, k);
    }

    T querySum(int l, int r, Node* curr) {
        if( curr->l > r || curr->r < l) return 0;
        else if( l <= curr->l && curr->r <= r ) return curr->sum;

        if(!curr->left || !curr->right) return neutro; // No changes here
        return merge(querySum(l, r, curr->left), querySum(l, r, curr->right));
    }


    // Methods to call
    Node* updateVal(int idx, T val, int version = -1) {
        Node *curr = version != -1 ? versions[version] : versions.back();
        versions.push_back(updateVal(idx, curr, val));
        return versions.back();
    }

    T queryKthSmallest(int l, int r, int k) {
        return queryKthSmallest(versions[l], versions[r], k);
    }

    T querySum(int l, int r, int version) {
        return querySum(l, r, versions[version]);
    }
};


SegTreePers<int> *ST;

vector< int > versions;
vector<int> values;
int timee = 0;

void dfs_st(int u, int p = -1) {
    int val = values[u-1];
    if(p == -1){
        ST->updateVal(val, 1);
    } else {
        ST->updateVal(val, 1, versions[p]);
    }
    versions[u] = SZ(ST->versions) - 1;

    for(auto v: adjList[u]){
        if(v == p) continue;
        dfs_st(v, u);
    }
}



int main () {
	fastIO();
	
	int n, q; cin>>n>>q;

    adjList.resize(n+1);
    depth.resize(n+1);
    versions.resize(n+1);
    
    values.resize(n);
    
    for(auto &x: values) cin>>x;

    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v; 
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    const int maxA = 1e9+10;

    ST = new SegTreePers<int>(0, maxA+1);

    dfs_prec(1);
    prec();
    dfs_st(1);



    auto get_how_many = [&](int l, int r, int node_l, int node_r) {
        int left = (node_l != 1 ? ST->querySum(l, r, versions[ ancestors[node_l][0] ]) : 0);
        int right = ST->querySum(l, r, versions[node_r]);
        return left+right;
    };




    while(q--){
        int u, v, k; cin>>u>>v>>k;
        if(depth[u] < depth[v]) swap(u, v);
        
        if(u == v) {
            cout << values[u-1] << endl;
            continue;
        }

        int lca = get_lca(u, v);
        // debugg(lca);

        int lca_is_kth_ancestor_of_u = depth[u] - depth[lca];
        int before_lca = get_kth_parent(u, lca_is_kth_ancestor_of_u-1);

        // debugg(before_lca);
        // debugg(u);

        // debugg(lca);
        // debugg(v);


        // int query_u_l = versions[before_lca];
        // int query_u_r = versions[u];

        // int query_v_l = versions[lca];
        // int query_v_r = versions[v];


        int l = 1, r = maxA, ans = -1;
        while(l <= r){
            int mid = l + (r-l) / 2;

            int how_many_u_path = get_how_many(l, mid, before_lca, u);
            int how_many_v_path = get_how_many(l, mid, lca, v);

            int total = how_many_u_path + how_many_v_path;

            if(k <= total) {
                ans = mid;
                r = mid-1;
            } else {
                k -= total;
                l = mid+1;
            }
        }

        cout << ans << endl;


    }



	return 0;
}

