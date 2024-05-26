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


const int MOD = 1e9+9;

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

const lli sqrt5 = 383008016;
const lli inv_sqrt5 = powerMod(sqrt5, MOD-2);
const lli inv_2 = (MOD+1)/2;

struct Node{

    int l=0, r=0;

    lli ls=0, rs=0;
    bool flagLazy = false;
    lli lazy_ls=0, lazy_rs=0;

    Node(){}
    Node(int l, int r): l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(l, b.r);
        res.ls = (ls + b.ls) % MOD;
        res.rs = (rs + b.rs) % MOD;

        return res;
    }

    // Update range
    void updateNode(lli sum_l, lli sum_r) {
        ls = (ls + sum_l) % MOD;
        rs = (rs + sum_r) % MOD;

        lazy_ls = (lazy_ls + sum_l) % MOD;
        lazy_rs = (lazy_rs + sum_r) % MOD;
        flagLazy = true;
    }

    void resetLazy() {
        flagLazy = false;
        lazy_ls = 0;
        lazy_rs = 0;
    }
};

struct SegmentTree {
    vector<Node> ST;
    int N;
    lli x, x_inv;

    SegmentTree(int n, lli x): N(n), x(x) {
        x_inv = powerMod(x, MOD-2);
        ST.resize(4*N);
        build(1, 1, N);
    }

    void build(int curr, int l, int r){
        ST[curr].l = l, ST[curr].r = r;

        if(l == r) return;
        int mid = l + (r-l)/2;
        build(2*curr, l, mid);
        build(2*curr+1, mid+1, r);
    }

    void pushToChildren(int curr){
        if(ST[curr].flagLazy){
            int size_child_left  = (ST[2*curr].r   - ST[2*curr].l + 1);
            int size_child_right = (ST[2*curr+1].r - ST[2*curr+1].l + 1);

            lli sum_r_to_left  = ST[curr].lazy_rs * powerMod(x_inv, size_child_right) % MOD;
            lli sum_l_to_right = ST[curr].lazy_ls * powerMod(x, size_child_left) % MOD;

            ST[2*curr].updateNode(ST[curr].lazy_ls, sum_r_to_left);
            ST[2*curr+1].updateNode(sum_l_to_right, ST[curr].lazy_rs);

            ST[curr].resetLazy();
        }
    }

    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, int start)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            int offset_l = l - start + 1;
            int offset_r = offset_l + (r-l+1) - 1;
            ST[curr].updateNode(powerMod(x, offset_l), powerMod(x, offset_r + 1));
            return;
        }

        pushToChildren(curr);

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, start);
        update(2*curr+1, mid+1, r, ql, qr, start);

        ST[curr] = ST[2*curr] + ST[2*curr+1];
    }
    void update(int ql, int qr, int start){
        update(1, 1, N, ql, qr, start);
    }
    
    // QUERY
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return ST[curr];
        else {
            pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    lli query(int ql, int qr){
        auto ans = query(1, 1, N, ql, qr);
        
        return (ans.ls - ans.rs + MOD) * powerMod(1 - x + MOD, MOD-2) % MOD;;
    }
};


int main () {
	fastIO();

	int n, q; cin>>n>>q;

    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];

    forr(i, 1, n) nums[i] = (nums[i-1] + nums[i]) % MOD;

    auto query_sum = [&](int l, int r){
        return (nums[r] - nums[l-1] + MOD) % MOD; 
    };

    lli phi      = (1 + sqrt5) * inv_2 % MOD; 
    lli conj_phi = (1 - sqrt5 + MOD) * inv_2 % MOD;

    SegmentTree ST_phi(n, phi), ST_conj(n, conj_phi);

    while(q--) {
        int t, l, r; cin>>t>>l>>r;

        if(t == 1) {
            ST_phi.update(l, r, l);
            ST_conj.update(l, r, l);
        } else {
            lli sum_phi = ST_phi.query(l, r);
            lli sum_conj = ST_conj.query(l, r);
            
            lli sum_fib = (sum_phi - sum_conj + MOD) * inv_sqrt5 % MOD;

            cout << (sum_fib + query_sum(l, r)) % MOD << endl;
        }
    }


	return 0;
}