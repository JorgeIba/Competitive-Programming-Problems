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


template <typename T,typename S>
struct SegmentTreeItLazy{ // 0 - indexed
	T neutro = 0, neutro_lazy = 0;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;

	SegmentTreeItLazy(int n, T val = 0,  const vector<S> &v = vector<S>()){
		st.resize(2*n);
        if(v.empty()) fill(all(st), val);
		size = n;
		delUp.resize(n, neutro_lazy);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
        if(!v.empty()) forn(i,n) st[i+size] = set(v[i]);
		build();
	}

	T merge(T a, T b){
		return max(a,b);
	}
	void apply(int i, T val, int k){
		st[i] += val;
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
	void update(int l, int r, T val){
		push(l += size), push(r += size);
		int ll = l, rr = r, k = 1;
		for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
			if (l & 1) apply(l++, val, k);
			if (~r & 1) apply(r--, val, k);
		}
		build(ll), build(rr);
	}
	T query(int l, int r){
                T ansL = neutro;
        	T ansR = neutro;
                push(l += size);
                push(r += size);
                for (; l <= r; l >>= 1, r >>= 1){
                        if (l & 1) ansL = merge(ansL, st[l++]);
                        if (~r & 1) ansR = merge(st[r--], ansR);
                }
                return merge(ansL, ansR);
        }
	T& operator[](int i) { push(i+size); return st[i + size]; }
	T set(S x){
		return x;
	}
};


const int MAXN = 2e5 + 100;

vector<int> adjList[MAXN];
int h[MAXN];

lli dp[MAXN];
int k;

lli cost(int u, int v){
    if(h[u] <= h[v]) return h[v] - h[u];
    return k - h[u] + h[v];
}

lli f(int u){
    lli &ans = dp[u];
    if(ans != -1) return ans;

    ans = 0;

    for(auto v: adjList[u]){
        ans = max(ans, cost(u, v) + f(v));
    }

    return ans;
}

void main_(){

    int n, m; cin>>n>>m>>k;

    forn(i, n) cin>>h[i];

    vector<int> income(n);
    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        income[v]++;
    }


    vector<int> init;
    for(int i = 0; i < n; i++){
        if(income[i] == 0) init.push_back(i);
    }


    sort(all(init), [&](int u, int v){
        return h[u] < h[v];
    });

    vector<lli> dps;
    fill(dp, dp+n, -1);
    for(auto s: init){
        dps.push_back(h[s] + f(s));
    }

    int l = SZ(init);


    SegmentTreeItLazy<lli,lli> ST(l);
    forn(i, l){
        ST.update(i, i, dps[i]);
    }

    lli ans = *max_element(all(dps));


    forn(i, l){
        int u = init[i];
        lli st = h[u];
        ST.update(i, l-1, -st);
        if(i){
            ST.update(0, i-1, k-st);
        }


        ans = min(ans, ST.query(0, l-1));


        if(i){
            ST.update(0, i-1, -(k-st));
        }
        ST.update(i, l-1, st);
    }

    cout << ans << endl;



    forn(i, n) adjList[i].clear();

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

