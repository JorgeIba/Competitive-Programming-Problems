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


const lli INF = 1e15;
struct Node{
    lli pref=-INF, suff=-INF, total=0, ans=-INF;

    Node(){}
    Node(lli pref, lli suff, lli total, lli ans): pref(pref), suff(suff), total(total), ans(ans) {
        // pref = max(pref, 0LL);
        // suff = max(suff, 0LL);
        // ans  = max(ans , 0LL);
    }

    Node operator+(const Node& b) {
        Node res;
        res.pref = max(pref, total + b.pref);
        res.suff = max(b.suff, b.total + suff);
        res.total = total + b.total;
        res.ans = max({ans, b.ans, res.pref, res.suff, res.total, suff + b.pref});
        return res;
    }
};

// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = Node();
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
		return Node(x, x, x, x);
	}
	T& operator[](int i) { return st[i + size]; }
};




int main () {
	fastIO();
    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    SegmentTreeIt<Node, lli> *ST = new SegmentTreeIt<Node, lli>(n, Node(), nums);


    int q; cin>>q;
    while(q--) {
        int t, x, y; cin>>t>>x>>y;

        if(t == 0) {
            ST->update(x-1, Node(y,y,y,y));
        } else {
            cout << ST->query(x-1, y-1).ans << endl;
        }

    }


	return 0;
}

