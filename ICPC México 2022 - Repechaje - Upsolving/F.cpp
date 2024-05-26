#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

const int maxN = 2e5+100;
const int inf = 2e9;
struct Node{
    int ans = 0, mn = inf, mx = -inf;
};



// Build on O(n log n) time and space, queries in O(1) for any operation
// Initialize OP and NEUTRO
// 0 - indexed
template<typename T>
struct DisjointSparseTable{
	vector<vector<T>> left, right;
	int K, N;

    typedef function<T(T, T)> typeFun;
    T NEUTRO;
    typeFun OP;

	DisjointSparseTable(const vector<T> &arr, T neutro, typeFun op): NEUTRO(neutro), OP(op){
		N = arr.size();
		K = log2(N) + 2;
		left.assign(K + 1, vector<T>(N));
		right.assign(K + 1, vector<T>(N));
		for(int j = 0; (1 << j) <= N; ++j){
			int mask = (1 << j) - 1;
			T acum = NEUTRO;
			for(int i = 0; i < N; ++i){
                acum = OP(acum, arr[i]);
				left[j][i] = acum;
				if((i & mask) == mask) acum = NEUTRO;
			}
			acum = NEUTRO; 
			for(int i = N-1; i >= 0; --i){
				acum = OP(arr[i], acum);
				right[j][i] = acum;
				if((i & mask) == 0) acum = NEUTRO; 
			}
		}
	}

	T query(int l, int r){
		if(l == r) return left[0][l];
		int i = 31 - __builtin_clz(l^r);
		return OP(right[i][l], left[i][r]);
	}
};






template<typename T>
struct SegmentTree {
    int N;
    DisjointSparseTable<Node> *DST;
    vector<Node> ST;
    vector<pair<int,int>> lazy;

    SegmentTree(int n, const vector<T> &values): N(n){
        ST.resize(4*N);
        lazy.resize(4*N, {0,-1});
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].ans = 0;
        ST[curr].mn = ST[curr].mx = value;
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].ans = max( {ST[2*curr].ans, ST[2*curr + 1].ans, ST[2*curr+1].mx - ST[2*curr].mn} );
        ST[curr].mn = min( ST[2*curr].mn, ST[2*curr+1].mn );
        ST[curr].mx = max( ST[2*curr].mx, ST[2*curr+1].mx );
    }


    //* NODE UPDATES *//
    void updateNode(int curr, int l, int r, int l_start, int &k){
        int new_l = k + (l - l_start);
        int new_r = new_l + (r - l);

        auto curr_node = DST->query(new_l-1, new_r-1);

        ST[curr].ans = curr_node.ans;
        ST[curr].mx = curr_node.mx;
        ST[curr].mn = curr_node.mn;
        
        lazy[curr].first = l_start;
        lazy[curr].second = k;
    }

    //* LAZY MANAGMENT *//
    void pushToChildren(int curr, int l, int r){
        if(lazy[curr].second != -1){
            updateNode(2*curr, l, (l+r)/2, lazy[curr].first, lazy[curr].second);
            updateNode(2*curr+1, (l+r)/2 + 1, r, lazy[curr].first, lazy[curr].second);
            lazy[curr].second = -1;
        }
    }
    
    //* UPDATES *//
    // SUM
    void update(int curr, int l, int r, int ql, int qr, int l_start, int &k)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNode(curr, l, r, l_start, k);
            return;
        }

        pushToChildren(curr, l, r);

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, l_start, k);
        update(2*curr+1, mid+1, r, ql, qr, l_start, k);

        updateFromChildren(curr);
    }
    void update(int ql, int qr, int &value){
        update(1, 1, N, ql, qr, ql, value);
    }
    

    Node merge(const Node &a, const Node &b) {
        Node c;
        if(b.mx != -inf && a.mn != inf)
            c.ans = max( {a.ans, b.ans, b.mx - a.mn} );
        else 
            c.ans = max(a.ans, b.ans);
        c.mn = min( a.mn, b.mn );
        c.mx = max( a.mx, b.mx );
        return c;
    }

        
    //? QUERIES ?//
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        else if(ql <= l && r <= qr) return ST[curr];
        else {
            pushToChildren(curr, l, r);
            int mid = l + (r-l) / 2;
            return merge(query(2*curr, l, mid, ql, qr), query(2*curr+1, mid+1, r, ql, qr));
        }
    }
    Node query(int ql, int qr){
        return query(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        if(l == r) {
            init_leaf(curr, values[l-1]);
        } else {
            int mid = (l+r)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            updateFromChildren(curr);
        }
    }
};


int main () {
	fastIO();

    int n, q; cin>>n>>q;

    vector<int> fence(n), machine(2*n);

    for(auto &x: fence) cin>>x;
    for(int i = 0; i < n; i++) {
        cin>>machine[i];
        machine[i+n] = machine[i];
    }


    vector<Node> machine_nodes(2*n);
    for(int i = 0; i < 2*n; i++) {
        int value = machine[i];
        machine_nodes[i].ans = 0;
        machine_nodes[i].mn = value;
        machine_nodes[i].mx = value;
    }


    Node neutro;    

    auto combine = [&](const Node &a, const Node &b){
        Node c;
        if(b.mx != -inf && a.mn != inf)
            c.ans = max( {a.ans, b.ans, b.mx - a.mn} );
        else 
            c.ans = max(a.ans, b.ans);
        c.mn = min( a.mn, b.mn );
        c.mx = max( a.mx, b.mx );
        return c;
    };

    DisjointSparseTable<Node> *DST = new DisjointSparseTable<Node>(machine_nodes, neutro, combine);

    SegmentTree<int> *SegTree = new SegmentTree<int>(n, fence);
    SegTree->DST = DST;
    while(q--) {
        int t; cin>>t;

        if(t == 2) {
            int l, r; cin>>l>>r;
            l++, r++;
            auto ans = SegTree->query(l, r);
            cout << ans.ans << endl;
        } else {
            int l, r, k; cin>>l>>r>>k;
            l++, r++, k++;
            SegTree->update(l, r, k);
            // SegTree->debug_tree(1, 1, n);
            cout << SegTree->query(1, n).ans << endl;
        }
    }


	return 0;
}

