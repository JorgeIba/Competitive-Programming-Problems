#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < n; i++)

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
		for(st[i += size] += val; i > 1; i >>= 1)
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




int main () {
	//fastIO();
	
    int n; cin>>n;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    SegmentTreeIt<lli,lli> *ST_2_inversions = new SegmentTreeIt<lli,lli>(n+1, 0);
    SegmentTreeIt<lli,lli> *ST_3_inversions = new SegmentTreeIt<lli,lli>(n+1, 0);

    lli ans = 0;
    for(int i = n-1; i >= 0; i--) {
        auto num = nums[i];

        ans += ST_3_inversions->query(0, num-1);

        lli inversions_2 = ST_2_inversions->query(0, num-1);
        

        ST_2_inversions->update(num, 1);
        ST_3_inversions->update(num, inversions_2);
    }   

    cout << ans << endl;

	return 0;
}

