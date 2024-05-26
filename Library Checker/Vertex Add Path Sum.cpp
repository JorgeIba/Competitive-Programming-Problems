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


struct Node{
    lli value=0, sum=0;
    lli lazy = 0;
    bool flagLazy = false;

    lli l, r;

    Node(){}
    Node(lli value, int l, int r): value(value), sum(value), l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(0, l, b.r);
        res.sum = sum + b.sum;
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
        
        ST[curr].value = value;
        ST[curr].sum += sz*value;

        ST[curr].lazy += value;
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
    T query(int ql, int qr){
        return query(1, 1, N, ql, qr).sum;
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
    bool valuesInEdges=false;
    int cnt = 1;

    HeavyLight(int n): depth(n), parent(n), subtree(n), chainHead(n), indexDS(n) {}
    
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
        for(; chainHead[u] != chainHead[v]; u = parent[ chainHead[u] ]){
            if( depth[ chainHead[u] ] < depth[ chainHead[v] ] ) swap(u, v);
            op(indexDS[chainHead[u]], indexDS[u]);
        }

        if(depth[u] > depth[v]) swap(u, v);
    
        op(indexDS[u], indexDS[v]);
    }

    template<class DSType>
    T query(int u, int v, DSType *DS) {
        T ans = T();
        traversePath(u, v, [this, &ans, DS](int l, int r) {
            ans += DS->query(l, r);
        });
        return ans;
    }

    template<class DSType>
    void update(int u, int v, T val, DSType *DS) {
        traversePath(u, v, [this, &val, DS](int l, int r) {
            DS->update(l, r, val);
        });
    }
};



void main_(){
    int n, q; cin>>n>>q;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    vector< vector<int> > adjList(n+1);
    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v; u++, v++;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    HeavyLight<lli> *HLD = new HeavyLight<lli>(n+1);
    HLD->dfs(adjList, 1);
    HLD->buildHLD(adjList, 1, 1);


    vector<lli> values(n);
    for(int i = 1; i <= n; i++) {
        values[  HLD->indexDS[i] - 1 ] = nums[i - 1];
    }

    SegmentTree<lli> *ST = new SegmentTree<lli>(n, values);
    
    while(q--) {
        int t; cin>>t;
        if( t == 0 ){
            int u, x; cin>>u>>x; u++;
            HLD->update(u, u, x, ST);
        }else {
            int u, v; cin>>u>>v; u++, v++;
            cout << HLD->query(u, v, ST) << endl;
        }
    }

}


int main () {
	fastIO();
	
	int t = 1; 
	// cin>>t;
	while(t--) 
		main_();


	return 0;
}

