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


const lli maxN = 1e5+10, INF = 1e15;
const bool neutro_lazy_set = false;
struct Node{
    lli l, r;

    lli pref=-INF, suff=-INF, total=0, ans=-INF;
    lli lazySET = 0;
    bool flagLazy = neutro_lazy_set;

    Node(){}
    Node(lli value) {
        // pref = max(0LL, value);
        // suff = max(0LL, value);
        pref = suff = value;
        total = value;
        ans = value;
    }


    Node operator+(const Node &b) {
        Node res;
        // Mantain Sum
        res.pref = max(pref, total + b.pref);
        res.suff = max(b.suff, b.total + suff);
        res.total = total + b.total;
        res.ans = max({ans, b.ans, res.pref, res.suff, res.total, suff + b.pref});
        return res;
    }

};

Node ST[4*maxN]; 

template<typename T>
struct SegmentTree {
    int N;
    

    SegmentTree(int n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value, int idx){
        ST[curr] = Node(value);
        ST[curr].l = ST[curr].r = idx;
    }

    //* NODE UPDATES *//
    void updateNodeSET(int curr, T value){
        lli sz = ST[curr].r - ST[curr].l + 1;
        // ST[curr].pref = max(0LL, sz*value);
        // ST[curr].suff = max(0LL, sz*value);

        ST[curr].pref = sz*value;
        ST[curr].suff = sz*value;

        ST[curr].total = sz*value;
        ST[curr].ans = max({ST[curr].pref, ST[curr].suff, ST[curr].total});

        ST[curr].flagLazy = true;
        ST[curr].lazySET = value;
    }

    void pushToChildren(int curr){
        if(ST[curr].flagLazy){
            updateNodeSET(2*curr, ST[curr].lazySET);
            updateNodeSET(2*curr+1, ST[curr].lazySET);
            ST[curr].flagLazy = false;
        }
    }

    Node updateFromChildren(Node left, Node right){
        return left + right;
    }
    
    // SUM
    void updateSET(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNodeSET(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateSET(2*curr, l, mid, ql, qr, value);
        updateSET(2*curr+1, mid+1, r, ql, qr, value);

        ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
    }
    void updateSET(int ql, int qr, T value){
        updateSET(1, 1, N, ql, qr, value);
    }
    
    
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        else if(ql <= l && r <= qr) return ST[curr];
        else {
            pushToChildren(curr);
            lli mid = (l+r) / 2;
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
            lli mid = (l+r)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
        }
    }
};



int main () {
	fastIO();
    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    SegmentTree<lli> *ST = new SegmentTree<lli>(n, nums);


    int q; cin>>q;
    while(q--) {
        int t, x, y; cin>>t>>x>>y;

        if(t == 0) {
            ST->updateSET(x, x, y);
        } else {
            cout << ST->query(x, y).ans << endl;
        }

    }


	return 0;
}

