#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli MOD = 1e9+7;
const lli maxN = 1e5+10;
const lli neutro_lazy_sum = 0;
struct Node{
    lli l, r;

    lli sum2;
    lli sum;
    lli lazySUM = neutro_lazy_sum;
};


template<typename T>
struct SegmentTree {
    lli N;
    Node ST[4*maxN]; 

    SegmentTree(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].sum2 = value*value % MOD;
        ST[curr].sum = value;
    }

    //* NODE UPDATES *//
    void updateNodeSUM(int curr, T value){
        lli l = ST[curr].l, r = ST[curr].r;

        (ST[curr].sum2 += 2 * value * ST[curr].sum % MOD + (r-l+1)*value % MOD * value % MOD) %= MOD;
        (ST[curr].sum += (r-l+1)*value % MOD) %= MOD;

        (ST[curr].lazySUM += value) %= MOD;
    }

    //* LAZY MANAGMENT *//
    void pushToChildren(int curr){
        if(ST[curr].lazySUM != neutro_lazy_sum){
            updateNodeSUM(2*curr, ST[curr].lazySUM);
            updateNodeSUM(2*curr+1, ST[curr].lazySUM);
            ST[curr].lazySUM = neutro_lazy_sum;
        }
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = (ST[2 * curr].sum + ST[2 * curr + 1].sum) % MOD;     
        ST[curr].sum2 = (ST[2 * curr].sum2 + ST[2 * curr + 1].sum2) % MOD;
    }
    
    //* UPDATES *//
    // SUM
    void updateSUM(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNodeSUM(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateSUM(2*curr, l, mid, ql, qr, value);
        updateSUM(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateSUM(int ql, int qr, T value){
        updateSUM(1, 1, N, ql, qr, value);
    }
    
    //? QUERIES ?//
    // SUM
    lli query_sum(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return 0;
        else if(ql <= l && r <= qr) return ST[curr].sum2;
        else {
            pushToChildren(curr);
            lli mid = (l+r) / 2;
            return (query_sum(2*curr, l, mid, ql, qr) + query_sum(2*curr+1, mid+1, r, ql, qr)) % MOD;
        }
    }
    lli query_sum(int ql, int qr){
        return query_sum(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1]);
        } else {
            lli mid = (l+r)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            updateFromChildren(curr);
        }
    }
};


int main () {
	//fastIO();

    lli n, q; cin>>n>>q;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    SegmentTree<lli> *ST = new SegmentTree<lli>(n, nums);

    while(q--) {
        char t; cin>>t;
        if(t == 'u') {
            lli l, r, x; cin>>l>>r>>x;
            if(x < 0) x += MOD;
            ST->updateSUM(l, r, x);
        } else {
            lli l, r; cin>>l>>r;
            cout << ST->query_sum(l, r) << endl;
        }
    }


	return 0;
}

