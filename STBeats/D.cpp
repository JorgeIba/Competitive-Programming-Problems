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
const lli maxN = 3e5+10;
const lli neutro_lazy_sum = 0;
struct Node{
    lli l, r;

    lli max;
    lli frMax;
    lli secondMax;

    lli sum;
    lli lazySUM = neutro_lazy_sum;
};


template<typename T>
struct SegmentTreeBeats {
    lli N;
    Node ST[4*maxN]; 


    static const int MIN = 0;
    static const int PLUS = 1;


    SegmentTreeBeats(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].max = ST[curr].sum = value;
        ST[curr].frMax = 1;
        ST[curr].secondMax = -INF;
    }
    
    void pushToChildren(int curr){
        
        if(ST[curr].lazySUM != neutro_lazy_sum){
            updateNodePLUS(2*curr, ST[curr].lazySUM);
            updateNodePLUS(2*curr+1, ST[curr].lazySUM);
            ST[curr].lazySUM = neutro_lazy_sum;
        }


        // Lazy is just ask if father is max than us or not
        updateNodeMIN(2*curr, ST[curr].max);
        updateNodeMIN(2*curr+1, ST[curr].max);
    }


    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = ST[2 * curr].sum + ST[2 * curr + 1].sum; 

        // Mantain max and second max and frMax
        ST[curr].max = max(ST[2 * curr].max, ST[2 * curr + 1].max);
        ST[curr].secondMax = max(ST[2*curr].secondMax, ST[2*curr+1].secondMax);
        ST[curr].frMax = 0;

        if(ST[curr].max == ST[2*curr].max){
            ST[curr].frMax += ST[2*curr].frMax;
        } else {
            ST[curr].secondMax = max(ST[curr].secondMax, ST[2*curr].max);
        }

        if(ST[curr].max == ST[2*curr+1].max){
            ST[curr].frMax += ST[2*curr+1].frMax;
        } else {
            ST[curr].secondMax = max(ST[curr].secondMax, ST[2*curr+1].max);
        }
    }


    bool breakCondition(int curr, int type_query, T value){
        switch (type_query) {
            case MIN: return ST[curr].max < value;
            // case EQUAL: return false; // leaves same
        }
        return false;
    }

    
    bool tagCondition(int curr, int type_query, T value){
        switch (type_query) {
            case MIN: return ST[curr].secondMax < value;
            // case EQUAL: return true; // leaves same
        }
        return true;
    }
    


    //* UPDATES *//

    // MIN
    void updateNodeMIN(int curr, T value){
        if(value < ST[curr].max){
            ST[curr].sum -= (ST[curr].max - value) * ST[curr].frMax;
            ST[curr].max = value;
        }
    }

    void updateMIN(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, MIN, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, MIN, value)){
            updateNodeMIN(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateMIN(2*curr, l, mid, ql, qr, value);
        updateMIN(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateMIN(int ql, int qr, T value){
        updateMIN(1, 1, N, ql, qr, value);
    }


    
    // PlUS 
    void updateNodePLUS(int curr, T value){
        ST[curr].max += value;
        if(ST[curr].secondMax != -INF) ST[curr].secondMax += value;
        ST[curr].sum += (ST[curr].r - ST[curr].l + 1) * value;

        ST[curr].lazySUM += value;
    }

    void updatePLUS(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, PLUS, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, PLUS, value)){
            updateNodePLUS(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updatePLUS(2*curr, l, mid, ql, qr, value);
        updatePLUS(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updatePLUS(int ql, int qr, T value){
        updatePLUS(1, 1, N, ql, qr, value);
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

    lli n; cin>>n;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    SegmentTreeBeats<lli> *beats = new SegmentTreeBeats<lli>(n, nums);
    
    lli q; cin>>q;

    for(int i = 0; i<q; i++)
    {
        lli t, l, r; cin>>t>>l>>r;
        if( t == 1 ){
            lli x; cin>>x;
            beats->updateMIN(l, r, x);
        }
        else if( t == 2 ){
            lli x; cin>>x;
            beats->updatePLUS(l, r, x);
        } else {
            cout << beats->query_sum(l, r) << endl;
        }

    }


	return 0;
}

