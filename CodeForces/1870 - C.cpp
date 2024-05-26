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

template <typename T>
struct SegmentTreeItMin{
	T neutro = T();
	int size;
	vector<T> st;
	SegmentTreeItMin(int n, T val = T()){
		st.resize(2*n);
		neutro = val;
        fill(all(st),val);
		size = n;
		build();
	}
	T merge(T a, T b){
    	return min(a, b);
	}
	void build(){
		for(int i = size - 1; i; i--)
			st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void update(int i, T val) {
        i += size;
        st[i] = min(st[i], val);
		for(; i > 1; i >>= 1)
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
	T& operator[](int i) { return st[i + size]; }
};

template <typename T>
struct SegmentTreeItMax{
	T neutro = T();
	int size;
	vector<T> st;
	SegmentTreeItMax(int n, T val = T()){
		st.resize(2*n);
		neutro = val;
        fill(all(st),val);
		size = n;
		build();
	}
	T merge(T a, T b){
    	return max(a, b);
	}
	void build(){
		for(int i = size - 1; i; i--)
			st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void update(int i, T val) {
        i += size;
        st[i] = max(st[i], val);
		for(; i > 1; i >>= 1)
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
	T& operator[](int i) { return st[i + size]; }
};



const int INF = 1e9;

void main_(){

    int n, k; cin>>n>>k;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    SegmentTreeItMin<int> STMin(k+2, INF);

    vector< pair<int,int> > limits(k+1, pair<int,int>{INF, -INF});
    for(int i = 0; i < n; i++){
        auto x = nums[i];
        STMin.update(x, i+1);
        auto idx_l = STMin.query(x, k);
        limits[x].first = min(limits[x].first, idx_l);
    } 

	SegmentTreeItMax<int> STMax(k+2, -INF);
    for(int i = n-1; i >= 0; i--){
        auto x = nums[i];
        STMax.update(x, i+1);
        auto idx_r = STMax.query(x, k);
        limits[x].second = max(limits[x].second, idx_r);
    } 


    forr(i, 1, k){
        if(limits[i].first == INF) cout << 0 << " ";
        else {
			auto [l, r] = limits[i];
            cout << 2 * (r - l + 1) << " ";
        }
    }

    cout << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

