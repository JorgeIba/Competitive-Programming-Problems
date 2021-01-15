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
    	return a + b;
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


string solve()
{
    lli n, k, m; cin>>n>>k>>m;
    vector<lli> B(m);
    for(auto &x: B) cin>>x;

    vector<lli> spaces(m+1);
    lli last = 0;
    for(int i = 0; i<m; i++)
    {
        spaces[i] = B[i] - last - 1;
        last = B[i];
    }
    spaces[m] = n - last;

    SegmentTreeIt<lli, lli> ST(SZ(spaces));

    lli sum_spaces = 0;
    for(int i = 0; i<SZ(spaces); i++)
    {
        //cout << spaces[i] << " ";
        sum_spaces += spaces[i];
        ST.update(i, spaces[i]);
    }
    if(sum_spaces % (k-1) != 0) return "NO";
    

    for(int i = 0; i<SZ(spaces)-1; i++)
    {
        lli l = i, r = i+1; //queries = (0, l), (r, SZ(spaces)-1);
        lli izq = ST.query(0, l);
        lli der = ST.query(r, m);

        if(izq >= (k/2) && der >= (k/2))
        {
            return "YES";
        }
        //cout << B[i] << " " << izq << " " << der << endl;
    }
    return "NO";
}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) cout << solve() << endl;

    
	return 0;
}