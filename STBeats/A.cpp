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


const lli INF = 1e18;
const lli maxN = 1e5+10;
struct Node{
    lli l, r;

    lli max;
    lli sum;
};


template<typename T>
struct SegmentTreeBeats {
    lli N;
    Node ST[4*maxN]; 


    static const int MOD = 0;
    static const int EQUAL = 1;


    SegmentTreeBeats(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].max = ST[curr].sum = value;
    }
    
    void pushToChildren(int curr){
        /*
        if(ST[curr].lazyMIN != neutro_lazy_min){
            updateNodeMin(2*curr, ST[curr].lazyMIN);
            updateNodeMin(2*curr+1, ST[curr].lazyMIN);
            ST[curr].lazyMIN = neutro_lazy_min;
        }
        */
    }


    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = ST[2 * curr].sum + ST[2 * curr + 1].sum; 

        // Mantain max
        ST[curr].max = max(ST[2 * curr].max, ST[2 * curr + 1].max);
    }


    bool breakCondition(int curr, int type_query, T value){
        switch (type_query) {
            case MOD: return ST[curr].max < value;
            case EQUAL: return false; // leaves same
        }
        return false;
    }

    
    bool tagCondition(int curr, int type_query, T value){
        switch (type_query) {
            case MOD: return ST[curr].l == ST[curr].r;
            case EQUAL: return true; // leaves same
        }
        return true;
    }
    


    //* UPDATES *//

    // MIN
    void updateNodeMOD(int curr, T value){
        ST[curr].max = ST[curr].sum = (ST[curr].max % value);
    }
    void updateMOD(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, MOD, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, MOD, value)){
            updateNodeMOD(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateMOD(2*curr, l, mid, ql, qr, value);
        updateMOD(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateMOD(int ql, int qr, T value){
        updateMOD(1, 1, N, ql, qr, value);
    }


    // EQUAL
    void updateNodeEQUAL(int curr, T value){
        ST[curr].max = ST[curr].sum = value;
    }
    void updateEQUAL(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, EQUAL, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, EQUAL, value)){
            updateNodeEQUAL(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateEQUAL(2*curr, l, mid, ql, qr, value);
        updateEQUAL(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateEQUAL(int ql, int qr, T value){
        updateEQUAL(1, 1, N, ql, qr, value);
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
    cout << "max: " << ST[curr].max  << ", sum: " << ST[curr].sum << " , frMax: " << ST[curr].frMax << " , secondMax: " << ST[curr].secondMax << endl;
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
	fastIO();

    lli n, q; cin>>n>>q;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    SegmentTreeBeats<lli> *beats = new SegmentTreeBeats<lli>(n, nums);

    for(int i = 0; i < q; i++)
    {
        lli t, ql, qr; cin>>t;
        if(t == 1)
        {   
            cin>>ql>>qr;
            cout << beats->query_sum(ql, qr) << endl;            
        } else if(t == 2){
            lli x; cin>>ql>>qr>>x;
            beats->updateMOD(ql, qr, x);
        } else {
            lli k, x; cin>>k>>x;
            beats->updateEQUAL(k, k, x);
        }

        // debug_tree(1, 1, n);
    }
    

	return 0;
}

