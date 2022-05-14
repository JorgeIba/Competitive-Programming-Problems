#include <bits/stdc++.h>
#include <tuple>
#include <utility>

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
typedef tuple<int,int,int> tiii;


template <typename T,typename S> 
struct SegmentTreeItLazy{ // 0 - indexed
	T neutro = make_tuple(0, 0, 0);
	lli neutro_lazy = 0;
	int size, height;
	vector<T> st;
	vlli delUp;
	vector<bool> upd;
    
    //S tipo de dato que recibe
	SegmentTreeItLazy(int n, T val,  const vector<S> &v = vector<S>()){
		st.resize(2*n);
        if(v.empty()) fill(all(st), val);
		size = n;
		delUp.resize(n, neutro_lazy);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
        if(!v.empty()) forn(i,n) st[i+size] = set(v[i]);
		/* build(); */
	}

	T merge(T a, T b){
		if(get<0>(a) == get<0>(b)){
            if(get<1>(a) == get<1>(b))
            {
                if(get<2>(a) < get<2>(b)) {
                    return a;
                }
                return b;
            }
			if(get<1>(a) < get<1>(b))
				return a;
			return b;
		}
		if(get<0>(a) > get<0>(b))
			return a;
		return b;
		//return a * b;
		//return __gcd(a, b);
		//return min(a, b);
	}
	void apply(int i, lli val, int k){
		get<0>(st[i]) += val; 
		if (i < size) delUp[i] += val, upd[i] = 1;
	}
	void calc(int i){
		if (!upd[i]) st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void build(){
		for(int i = size - 1; i; i--) calc(i);
	}
	void build(int p) {
		while (p > 1) p >>= 1, calc(p);
	}
	void push(int p) {
		for (int s = height, k = 1 << (height - 1); s; s--, k >>= 1){
			int i = p >> s;
			if (upd[i]){
				apply(i << 1, delUp[i], k);
				apply(i << 1 | 1, delUp[i], k);
				upd[i] = 0, delUp[i] = neutro_lazy;
			}
		}
	}
	void update(int l, int r, lli val){
		push(l += size), push(r += size);
		int ll = l, rr = r, k = 1;
		for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
			if (l & 1) apply(l++, val, k);
			if (~r & 1) apply(r--, val, k);
		}
		build(ll), build(rr);
	}
	T query(int l, int r){
		push(l += size), push(r += size);
		T res = neutro;
		for (; l <= r; l >>= 1, r >>= 1){
			if (l & 1) res = merge(res, st[l++]);
			if (~r & 1) res = merge(res, st[r--]);
		}
		return res;
	}
	T& operator[](int i) { return st[i + size]; }
	T set(S x){
		return x;
	}
};
const int MAXN = 2e5 + 5;

int n, k;
int A[MAXN];
/* int nxt[MAXN]; */
/* int cnt_after[MAXN]; */
/* int idx[MAXN]; */
int fi[MAXN];

void precal(SegmentTreeItLazy<tiii,tiii>& st){
	set<int> s;
	/* vi last(k + 1, n); */
	for(int i = n - 1; i >= 0; i--){
		if(fi[A[i]] == -1)
			fi[A[i]] = i;
		s.insert(A[i]);
		/* cnt_after[i] = s.size(); */
		/* nxt[i] = last[A[i]]; */
		/* last[A[i]] = i; */
		st[i] = make_tuple(s.size(), A[i], i);
		/* idx[A[i]] = i; */
	}
	st.build();
}

int main () {
	fastIO();
	cin >> n >> k;
	fi[n] = -1;
	forn(i, n){
		cin >> A[i];
		fi[i] = -1;
	}
	SegmentTreeItLazy<tiii,tiii> st(n, make_tuple(0, 0, -1));
	precal(st);
	vi ans;
	set<int> s;
	int i = 0;
	while(true){
		auto q = st.query(i, n - 1);
		if(get<0>(q) <= 0) break;
		if(s.count(get<1>(q))){
			st.update(get<2>(q), get<2>(q), -get<0>(q));
			continue;
		}
		assert(1 <= get<1>(q) && get<1>(q) <= k);
		s.insert(get<1>(q));
		ans.pb(get<1>(q));
		i = get<2>(q);
		/* while(i < idx[q.se]){ */
		/* 	if(idx[A[i]] == i){ */
		/* 		idx[A[i]] = nxt[i]; */
		/* 		st.update(A[i], make_pair(cnt_after[idx[A[i]]] + rest.query(i, i), A[i])); */
		/* 	} */
		/* 	i++; */
		/* } */
		st.update(0, fi[get<1>(q)], -1);
	}
	assert(SZ(ans) == k);
	assert(SZ(s) == k);
	/* for(auto x:ans) cout << x << ' '; */
	forn(j, SZ(ans)){
		cout << ans[j];
		if(j + 1 < SZ(ans))
			cout << ' ';
	}
	cout << endl;
	return 0;
}
