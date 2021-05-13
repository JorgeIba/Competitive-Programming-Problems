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

// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = 0;
	int size;
	vector<T> st;
	SegmentTreeIt(int n, T val = 0, const vector<S> &v = vector<S>()){
		st.resize(2*n);
		if(v.empty())
			fill(all(st),val);
		size = n;
		if(!v.empty())
			forn(i,n) st[i+size] = set(v[i]);
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
		for(st[i += size] = val; i > 1; i >>= 1)
				st[i >> 1] = merge(st[i], st[i ^ 1]);
	}
	T query(int l, int r){
		T ans = neutro;
		for(l += size, r += size; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ans = merge(ans, st[l++]);
			if (~r & 1) ans = merge(ans, st[r--]);
		}
		return ans;
	}
	T set(S x){
		return x;
	}
	T& operator[](int i) { return st[i + size]; }
};


SegmentTreeIt<lli,lli> *ST;
vector<lli> nums, pos, ans;


void dfs(int l, int r, int depth)
{
    
    if(l>r) return;
    lli maxi = ST->query(l, r);
    //cout << l << " " << r << " " << maxi << endl;
    int pos_maxi = pos[maxi];
    ans[pos_maxi] = depth;
    dfs(l, pos_maxi-1, depth+1);
    dfs(pos_maxi+1, r, depth+1);
}


void solve()
{
    int n; cin>>n;
    nums.resize(n);
    pos.resize(n);
    ans.resize(n);
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x; x--;
        nums[i] = x;
        pos[x] = i;
    }

    ST = new SegmentTreeIt<lli,lli>(n, 0, nums);

    dfs(0, n-1, 0);
    for(auto x: ans) cout << x << " ";
    cout << endl;
}


int main () {
	fastIO();
    int t; cin>>t; 
    while(t--) solve();


	return 0;
}