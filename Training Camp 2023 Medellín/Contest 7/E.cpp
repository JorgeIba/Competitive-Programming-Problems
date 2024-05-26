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

const int OR = 0;
const int XOR = 1;

struct Node{
    lli val = 0;
    int op = OR;

    Node(): val(0), op(OR) {}
    Node(int val): val(val), op(OR){}

    Node operator+(Node b){
        Node ans;
        assert(op == b.op);
        if(op == OR) {
            ans.val = val | b.val;
        } else {
            ans.val = val ^ b.val;
        }

        ans.op = op^1;
        return ans;
    }
};

// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = T();
	int size;
	vector<T> st;
	SegmentTreeIt(int n, const vector<S> &v = vector<S>()){
		st.resize(2*n);
		size = n;		
        forn(i,n) st[i+size] = set(v[i]);
		build();
	}
	T merge(T a, T b){
    	return a + b;
	}
	void build(){
		for(int i = size - 1; i; i--){
            st[i] = merge(st[i << 1], st[i << 1 | 1]);
            // cout << st[i<<1].val << " " << st[i<<1].op << " --- " << st[i<<1 | 1].val << " " << st[i<<1 | 1].op << " ---->> ";
            // cout << st[i].val << " -- " << st[i].op << endl;
        }
	}
	void update(int i, T val) {
		for(st[i += size] = val; i > 1; i >>= 1)
			if(i & 1)
				st[i >> 1] = merge(st[i^1], st[i]);
            else 
                st[i >> 1] = merge(st[i], st[i^1]);
	}
	int query(){
		return st[1].val;
	}
	T set(S x){
		return T(x);
	}
	T& operator[](int i) { return st[i + size]; }
};




int main () {
	fastIO();
	
    int n, m; cin>>n>>m;
    n = 1 << n;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    SegmentTreeIt<Node, int> ST(n, nums);

    while(m--){
        int idx, v; cin>>idx>>v; idx--;
        ST.update(idx, Node(v));

        cout << ST.query() << endl;
    }   


	return 0;
}

