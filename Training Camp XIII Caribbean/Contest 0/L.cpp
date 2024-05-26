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

// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = T();
	int size;
	vector<T> st;
	SegmentTreeIt(int n, T val = T(), const vector<S> &v = vector<S>()){
		st.resize(2*n);
		if(v.empty())
			fill(all(st),val);
		size = n;
		if(!v.empty())
			forn(i,n) st[i+size] = set(v[i]);
		build();
	}
	T merge(T a, T b){
    	return a + b;
	}
	void build(){
		for(int i = size - 1; i; i--)
			st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void update(int i, T val) {
		for(st[i += size] = val; i > 1; i >>= 1)
			if(i & 1)
				st[i >> 1] = merge(st[i^1], st[i]);
            else 
                st[i >> 1] = merge(st[i], st[i^1]);
	}
	T query(int l, int r){
		T ansL = neutro;
        T ansR = neutro;
		for(l += size, r += size; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ansL = merge(ansL, st[l++]);
			if (~r & 1) ansR = merge(st[r--], ansR);
		}
		return merge(ansL, ansR);
	}
	T set(S x){
		return T(x);
	}
	T& operator[](int i) { return st[i + size]; }
};


struct Node{
    lli total, best_pref;
    Node(): total(0) {
        best_pref = -1e15;
    }
    Node(lli val): total(val), best_pref(val) {
        best_pref = max(0LL, best_pref);
    }
    
    Node operator+(const Node &b) {
        Node c;
        c.total = total + b.total;
        c.best_pref = max(best_pref, total + b.best_pref);
        // c.max_pref = max(max_pref, c.best_pref)
        return c;
    }
};



int main () {
	//fastIO();


    int n, q; cin>>n>>q;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    
    SegmentTreeIt<Node, int> *ST = new SegmentTreeIt<Node, int>(n, Node(), nums);


    while(q--){
        int t; cin>>t;

        if(t == 1) {
            int k, u; cin>>k>>u; k--;
            ST->update(k, Node(u));
        } else {
            int l, r; cin>>l>>r; l--, r--;
            Node ans = ST->query(l, r);
            cout << ans.best_pref << endl;
        }
    }


	return 0;
}

