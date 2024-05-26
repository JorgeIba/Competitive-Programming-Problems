#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define pairr pair<lli,lli>

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;



const lli maxN = 2e5+10;
struct Node{
    lli l, r;

    lli max_value;
    lli idx;
};


Node ST[4*maxN]; 
template<typename T>
struct SegmentTree {
    lli N;

    SegmentTree(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value, int idx){
        ST[curr].max_value = value;
        ST[curr].idx = idx;
    }
    

    void updateFromChildren(int curr){
    	pairr left  = {ST[2*curr].max_value,     ST[2*curr].idx}; 
    	pairr right = {ST[2*curr + 1].max_value, ST[2*curr+1].idx};
		auto merged = merge(left, right);
		ST[curr].max_value = merged.first;
		ST[curr].idx = merged.second;
    }
    

    
    pairr merge(pairr a, pairr b) {
		if(a.first > b.first) {
			return a;
		} else if(a.first < b.first) {
			return b;
		} else {
			return {a.first, min(a.second, b.second)};
		}    	
    }
    
    
    //? QUERIES ?//
    // MAX
	pairr query_max(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return {-1e9, -1e9};
        else if(ql <= l && r <= qr) return {ST[curr].max_value, ST[curr].idx};
        else {
            lli mid = (l+r) / 2;
            auto left_ans = query_max(2*curr, l, mid, ql, qr);
            auto right_ans = query_max(2*curr+1, mid+1, r, ql, qr);
			
			return merge(left_ans, right_ans);
        }
    }
    pairr query_max(int ql, int qr){
        return query_max(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1], l);
        } else {
            lli mid = (l+r)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            updateFromChildren(curr);
        }
    }
};


vector< vector<lli> > dp;
SegmentTree<lli> *SegTree;

const lli MOD = 1e9+7;

lli f(lli l, lli r, lli m) {
    if(l > r) return 1;
	if(m <= 0) return 0;
	if(l == r) return m;

		
	lli pivot = SegTree->query_max(l, r).second;
	
    // cout << "l: " << l << " r:" << r << " m:" << m << " pivot:" << pivot << endl;

	lli &ans = dp[pivot][m];
	
	if(ans != -1) return ans;
	
	ans = f(l, r, m-1) + f(l, pivot-1, m-1)*f(pivot+1, r, m) % MOD;
	if(ans >= MOD) ans -= MOD;
	
	return ans;
}



void solve() {
	lli n, m; cin>>n>>m;
	
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	// cout << n << " 1--- " << m << endl;
    dp.clear();
	dp.assign(n+1, vector<lli>(m+1, -1));
	// cout << n << " 2--- " << m << endl;
	SegTree = new SegmentTree<lli>(n, nums);
	// cout << n << " 3--- " << m << endl;	
	cout << f(1, n, m) << endl;
}



int main () {
	//fastIO();
	
	int t; cin>>t;
	while(t--) solve();

	return 0;
}

