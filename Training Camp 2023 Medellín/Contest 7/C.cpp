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
	SegmentTreeIt(int n, T val = T()){
		st.resize(2*n);
        fill(all(st),val);
        neutro = val;
		size = n;
		build();
	}
	T merge(T a, T b){
    	return max(a,b);
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
	T set(S x){
		return T(x);
	}
	T& operator[](int i) { return st[i + size]; }
};


int main () {
	//fastIO();
	
    int n; cin>>n;

    vector< pair<lli,lli> > points(n);
    for(auto &[x, w]: points) cin>>x>>w;

    vector<lli> all_coords;
    for(auto [x, w]: points){
        all_coords.push_back(x+w);
        all_coords.push_back(x-w);
    }

    sort(all(all_coords));
    all_coords.erase(unique(all(all_coords)), all_coords.end());
    int m = SZ(all_coords);

    auto mapp = [&](lli x){
        return lower_bound(all(all_coords), x) - all_coords.begin();
    };

    SegmentTreeIt<lli,lli> ST(m+5, 0);

    sort(all(points));
    vector<int> next(n, -1);

    vector<int> dp(n, 0);
    for(int i = n-1; i >= 0; i--){
        auto [x, w] = points[i];

        auto ans = ST.query(mapp(x+w), m+4);
        dp[i] = ans + 1;
        ST.update(mapp(x-w), dp[i]);
    }

    cout << *max_element(all(dp)) << endl;


	return 0;
}

