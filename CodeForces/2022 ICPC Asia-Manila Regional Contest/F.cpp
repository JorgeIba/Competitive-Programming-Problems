#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;

typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

template <typename T, typename S>
struct SegmentTreeItMax{
	T neutro = {0, -1};
	int size;
	vector<T> st;
	SegmentTreeItMax(int n, T val = 0, const vector<S> &v = vector<S>()){
		st.resize(2*n);
		if(v.empty())
			fill(all(st),val);
		size = n;
		if(!v.empty())
			forn(i,n) st[i+size] = {v[i], i};
		build();
	}
	T merge(T a, T b){
		if(a.fi == b.fi){
			if(a.se < b.se) return a;
			return b;
		}
		if(a.fi > b.fi) return a;
    	return b;
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
	void print(){
		forn(i, size)
			cout << query(i, i).fi << ' ';
		cout << endl;
	}
};
template <typename T, typename S>
struct SegmentTreeItMin{
	T neutro = {1e18, -1};
	int size;
	vector<T> st;
	SegmentTreeItMin(int n, T val = 0, const vector<S> &v = vector<S>()){
		st.resize(2*n);
		if(v.empty())
			fill(all(st),val);
		size = n;
		if(!v.empty())
			forn(i,n) st[i+size] = {v[i], i};
		build();
	}
	T merge(T a, T b){
		if(a.fi == b.fi){
			if(a.se < b.se) return a;
			return b;
		}
		if(a.fi < b.fi)
			return a;
    	return b;
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
	void print(){
		forn(i, size)
			cout << query(i, i).fi << ' ';
		cout << endl;
	}
};

int main () {
	fastIO();
	int n;
	cin >> n;
	vlli v(n);
	vi nxt(n);
	vi prv(n);
	lli sum = 0;
	forn(i, n){
		cin >> v[i];
		sum += v[i];
		nxt[i] = i + 1;
		prv[i] = i - 1;
	}
	SegmentTreeItMax<pii,lli> st_max(n, {0, -1}, v);
	SegmentTreeItMin<pii,lli> st_min(n, {1e18, -1}, v);
	forn(i, n){
		auto mx = st_max.query(0, n - 1);
		pii ans;
		if((sum - mx.fi) < mx.fi){
			ans = st_min.query(0, n - 1);
		}
		else{
			ans = mx;
		}
		if(prv[ans.se] >= 0){
			auto L = st_max.query(prv[ans.se], prv[ans.se]);
			st_max.update(L.se, {L.fi + ans.fi / 2, L.se});
			st_min.update(L.se, {L.fi + ans.fi / 2, L.se});
			sum += ans.fi / 2;
			nxt[L.se] = nxt[ans.se];
		}
		if(nxt[ans.se] < n){
			auto R = st_max.query(nxt[ans.se], nxt[ans.se]);
			st_max.update(R.se, {R.fi + ans.fi / 2, R.se});
			st_min.update(R.se, {R.fi + ans.fi / 2, R.se});
			sum += ans.fi / 2;
			prv[R.se] = prv[ans.se];
		}
		st_max.update(ans.se, {0, -1});
		st_min.update(ans.se, {1e18, -1});
		sum -= ans.fi;
		/* st_max.print(); */
		/* st_min.print(); */
		/* cout << var(sum) << endl; */
		cout << ans.se + 1 << ' ' << ans.fi << endl;
	}
	return 0;
}
 