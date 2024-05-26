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
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int INF = 1e9;

template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = {INF, -1};
	int size;
	vector<T> st;
	SegmentTreeIt(int n, T val = {INF, -1}, const vector<S> &v = vector<S>()){
		st.resize(2*n);
		if(v.empty())
			fill(all(st),val);
		size = n;
		if(!v.empty())
			forn(i,n) st[i+size] = set(v[i]);
		build();
	}
	T merge(T a, T b){
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
		forn(i, size){
			auto q = query(i, i);
			cout << q.fi << ' ' << q.se << endl;
		}
	}
};

const int MAXN = 2e5 + 5;

int n, k, _e;
vi adj[MAXN];
int ini[MAXN], fin[MAXN], level[MAXN];
int node[MAXN], parent[MAXN];

void dfs(int u, int p, int lvl, SegmentTreeIt<pii,pii>& st){
	/* cout << var(u) << endl; */
	ini[u] = _e++;
	node[ini[u]] = u;
	level[u] = lvl;
	st.update(ini[u], {lvl, ini[u]});
	parent[u] = p;
	for(auto v:adj[u]){
		if(v == p) continue;
		dfs(v, u, lvl + 1, st);
	}
	fin[u] = _e++;
	node[fin[u]] = u;
	st.update(fin[u], {lvl, fin[u]});
}

int main () {
	fastIO();
	cin >> n >> k;
	forn(i, n - 1){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	SegmentTreeIt<pii,pii> st(2*n);
	dfs(0, -1, 0, st);
	/* st.print(); */
	vi ans;
	set<int> disp;
	disp.insert(0);
	while(!disp.empty()){
		auto u = *disp.begin();
		ans.pb(u);
		auto v = u;
		forn(i, k){
			if(v == -1) break;
			while(true){
				auto q = st.query(ini[v], fin[v]);
				/* cout << var(q.fi) << ' ' << var(q.se) << endl; */
				if((q.fi - level[v]) > (k - i)) break;
				disp.insert(node[q.se]);
				st.update(q.se, {INF, q.se});
				/* st.print(); */
			}
			v = parent[v];
		}
		disp.erase(u);
	}
	forn(i, SZ(ans)){
		cout << ans[i] + 1;
		if(i < SZ(ans) - 1)
			cout << ' ';
	}
	cout << endl;
	return 0;
}
