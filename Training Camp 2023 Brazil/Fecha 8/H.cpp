#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;



const lli INF = 1e18;
struct Node{
    lli mini =INF, sold=0;

    int l, r;

    Node(){}
    Node(lli val, int l, int r): mini(val), sold(0), l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(0, l, b.r);
        res.mini = min(mini, b.mini);
        res.sold = sold && b.sold;

        return res;
    }

    // Update range
    void updateNode(int new_val) {
        mini = new_val;
        sold = 1;
        // debugg(sold);
        // debugg(l);
        // debugg(r);
    }
};


// T Lo que le vas a pasar
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


    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            ST[curr].updateNode(value);
            return;
        }

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, value);
        update(2*curr+1, mid+1, r, ql, qr, value);

        ST[curr] = ST[2*curr] + ST[2*curr+1];
    }
    void update(int ql, int qr, T value){
        update(1, 1, N, ql, qr, value);
    }
    
    // QUERY
    lli query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return 0;
        else if(ql <= l && r <= qr) return ST[curr].sold;
        else {
            // pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    lli query(int ql, int qr){
        return query(1, 1, N, ql, qr);
    }


    
    lli find_leftmost(int curr, int l, int r, T val) {
        if(ST[curr].mini > val) return INF;

        if(l == r) {
            lli corr = ST[curr].mini;
            update(l, l, val+1);
            return corr;
        }

        int mid = l + (r-l)/2;

        if(ST[2*curr].mini <= val) {
            return find_leftmost(2*curr, l, mid, val);
        } else {
            return find_leftmost(2*curr+1, mid+1, r, val);
        }
    }



    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1], l);
        } else {
            int mid = l + (r-l)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            ST[curr] = ST[2*curr] + ST[2*curr+1];
        }
    }
};






int main () {
	//fastIO();
	
    int n; cin>>n;
    vector<int> items(n);
    for(auto &x: items) cin>>x;

    int m; cin>>m;
    vector<int> budgets(m);
    for(auto &x: budgets) cin>>x;


    SegmentTree<int> *ST = new SegmentTree<int>(n, items);

    for(auto x: budgets){
        ST->find_leftmost(1, 1, n, x);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += ST->query(i, i);
    }
    cout << ans << endl;


	return 0;
}

