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


/* 
    Supports:
    Range update SUM 1 + 2 + 3 + 4 + 5 ... in [ql, qr]
    Range query sum(l, r)
*/

const lli maxN = 2e5+10;
const lli neutro_lazy_sub = 0;
const lli neutro_lazy_times = 0;
struct Node{
    lli l, r;

    lli value;
    lli sum;
    lli lazySUB = neutro_lazy_sub;
    lli lazyManyTimes = neutro_lazy_times;
};

lli gauss(lli n) {
    return n*(n+1)/2;
}


template<typename T>
struct SegmentTree {
    lli N;
    Node ST[4*maxN]; 

    SegmentTree(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].value = value;
        ST[curr].sum = value;
    }

    //* NODE UPDATES *//
    void updateNodeSUM(int curr, T value, lli how_many_times = 1){
        lli l = ST[curr].l, r = ST[curr].r;
        ST[curr].sum += how_many_times*(gauss(r) - gauss(l-1)) - value*(r-l+1);
        ST[curr].value += (l - value);

        ST[curr].lazySUB += value;
        ST[curr].lazyManyTimes += how_many_times;
    }

    //* LAZY MANAGMENT *//
    void pushToChildren(int curr){
        if(ST[curr].lazyManyTimes != neutro_lazy_times){
            updateNodeSUM(2*curr, ST[curr].lazySUB, ST[curr].lazyManyTimes);
            updateNodeSUM(2*curr+1, ST[curr].lazySUB, ST[curr].lazyManyTimes);
            ST[curr].lazySUB = neutro_lazy_sub;
            ST[curr].lazyManyTimes = neutro_lazy_times;
        }
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = ST[2 * curr].sum + ST[2 * curr + 1].sum;     
    }

    //* UPDATES *//
    // SUM 1 + 2 + 3 + 4 + 5 ... in [ql, qr]
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
        else if(ql <= l && r <= qr) return ST[curr].sum;
        else {
            pushToChildren(curr);
            lli mid = (l+r) / 2;
            return query_sum(2*curr, l, mid, ql, qr) + query_sum(2*curr+1, mid+1, r, ql, qr);
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
    
    /*
        void debug(int curr){
            cout << "Range: [" << ST[curr].l << ", " << ST[curr].r << "], Value: " << ST[curr].value << ", SUM: " << ST[curr].sum << ", LazySUB: " << ST[curr].lazySUB << endl;
        }
        void debug_tree(int curr, int l, int r){
            if(l == r) {
                cout << l << " leaf -> "; debug(curr);
            } else {

                pushToChildren(curr);
                lli mid = (l+r)/2;
                debug_tree(2*curr, l, mid);
                debug_tree(2*curr+1, mid+1, r);
                updateFromChildren(curr);

                cout << "not leaf -> "; debug(curr);
            }
        }
    */
    
};



int main () {
	// fastIO();


    lli n, q; cin>>n>>q;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    SegmentTree<lli> *ST = new SegmentTree<lli>(n, nums);

    while(q--) {
        lli t, l, r; cin>>t>>l>>r;

        if(t == 1) {
            ST->updateSUM(l, r, l-1);
        } else {
            cout << ST->query_sum(l, r) << endl;
        }
    }


	return 0;
}

