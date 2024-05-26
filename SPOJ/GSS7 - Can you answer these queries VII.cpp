#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


const lli INF = 1e15;
struct Node{
    lli pref = -INF, suff = -INF, total = 0, ans = -INF;
    lli lazy = 0;
    bool flagLazy = false;

    lli l, r;

    Node(){}
    Node(lli value, int l, int r): pref(value), suff(value), total(value), ans(value), l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(0, l, b.r);

        res.pref = max(pref, total + b.pref);
        res.suff = max(b.suff, b.total + suff);
        res.total = total + b.total;
        res.ans = max({ans, b.ans, res.pref, res.suff, res.total, suff + b.pref});
        return res;
    }
};

template<typename T>
struct SegmentTree {
    vector<Node> ST;
    int N;

    SegmentTree(int n, const vector<T> &values): N(n){
        ST.resize(4*N);
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value, int idx){
        ST[curr] = Node(value, idx, idx);
    }

    //* NODE UPDATES *//
    void updateNode(int curr, T value){
        lli sz = ST[curr].r - ST[curr].l + 1;
        
        ST[curr].pref  = sz*value;
        ST[curr].suff  = sz*value;
        ST[curr].total = sz*value;
        ST[curr].ans   = sz*value;

        ST[curr].lazy = value;
        ST[curr].flagLazy = true;
    }

    void pushToChildren(int curr){
        if(ST[curr].flagLazy){
            updateNode(2*curr, ST[curr].lazy);
            updateNode(2*curr+1, ST[curr].lazy);
            ST[curr].flagLazy = false;
        }
    }

    Node updateFromChildren(Node left, Node right){
        return left + right;
    }
    
    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNode(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, value);
        update(2*curr+1, mid+1, r, ql, qr, value);

        ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
    }
    void update(int ql, int qr, T value){
        update(1, 1, N, ql, qr, value);
    }
    
    // QUERY
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        else if(ql <= l && r <= qr) return ST[curr];
        else {
            pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    Node query(int ql, int qr){
        return query(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1], l);
        } else {
            int mid = l + (r-l)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
        }
    }
};


template<typename T = int>
struct HeavyLight{
    vector<int> depth, parent, subtree, chainHead, indexDS;
    bool valuesInEdges;
    int cnt = 1;

    HeavyLight(int n, bool valuesInEdges = false): depth(n), parent(n), subtree(n), chainHead(n), indexDS(n), valuesInEdges(valuesInEdges) {}
    
    template<class G>
    void dfs(const G &adjList, int u, int p = -1) {
        subtree[u] = 1;
        for(auto v: adjList[u]) {
            if( v == p ) continue;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(adjList, v, u);

            subtree[u] += subtree[v];
        }
    }

    template<class G>
    void buildHLD(const G &adjList, int u, int head, int p = -1) {
        chainHead[u] = head;
	    indexDS[u] = cnt++;

        int heavy = -1, sz_heavy = 0;
        for(auto v: adjList[u]){
            if(v == p) continue;
            if(sz_heavy < subtree[v]) heavy = v, sz_heavy = subtree[v];
        }

        if(heavy != -1) 
            buildHLD(adjList, heavy, head, u);

        for(auto v: adjList[u]) {
            if(v == p || v == heavy) continue;
            buildHLD(adjList, v, v, u);
        }	
    }

    template<class BinaryOperation>
    void traversePath(int u, int v, BinaryOperation op) {
        if(valuesInEdges && u == v) {
            op(indexDS[u], indexDS[u], true);
            return;
        }

        bool left = true;
        for(; chainHead[u] != chainHead[v]; u = parent[ chainHead[u] ]){
            if( depth[ chainHead[u] ] < depth[ chainHead[v] ] ) {
                swap(u, v);
                left = !left;
            }
            op(indexDS[chainHead[u]], indexDS[u], left);
        }

        if(depth[u] > depth[v])
            swap(u, v);
        else
            left = !left;
        
        if(valuesInEdges && u == v) return;
        op(indexDS[u] + valuesInEdges, indexDS[v], left);
    }

    template<class DSType>
    T query(int u, int v, int n, DSType *DS_L, DSType *DS_R) {
        T ansL = T();
        T ansR = T();
        traversePath(u, v, [this, &ansL, &ansR, &n, DS_L, DS_R](int l, int r, bool left = true) {
            if(left) 
                ansL = ansL + DS_L->query(n + 1 - r , n + 1 - l);
            else 
                ansR = DS_R->query(l, r) + ansR;                
        });
        return ansL + ansR;
    }

    template<class DSType>
    void update(int u, int v, int val, int n, DSType *DS_L, DSType *DS_R) {
        traversePath(u, v, [this, &val, n, DS_L, DS_R](int l, int r, bool left = true) {
            DS_L->update(n + 1 - r , n + 1 - l, val);
            DS_R->update(l, r, val);
        });
    }
};


int main () {
	fastIO();
	
    int n; cin>>n;

    vector<lli> nums(n);
    for(int i = 0; i < n; i++) cin>>nums[i];


    vector< vector<int> > adjList(n+1);
    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    HeavyLight<Node> *HLD = new HeavyLight<Node>(n+1);
    HLD->dfs(adjList, 1);
    HLD->buildHLD(adjList, 1, 1);


    vector<lli> values(n);
    for(int i = 1; i <= n; i++){
        values[  HLD->indexDS[i] - 1 ] = nums[i-1];
    }

    auto c_values = values;

    reverse(all(c_values));

    SegmentTree<lli> *ST_L = new SegmentTree<lli>(n, c_values);
    SegmentTree<lli> *ST_R = new SegmentTree<lli>(n, values);

    int q; cin>>q;
    while(q--) {
        int t; cin>>t;
        if(t == 1) {
            int a, b; cin>>a>>b;
            Node ans = HLD->query(a, b, n, ST_L, ST_R);
            cout << max(0LL, ans.ans) << endl;
        } else {
            int a, b, c; cin>>a>>b>>c;

            HLD->update(a, b, c, n, ST_L, ST_R);
        }
    }
    
	return 0;
}

