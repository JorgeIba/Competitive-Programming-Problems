#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

// It supports values in vertices or in edges
// Call first dfs and then build
// dfs(adjList, root)
// build(adjList, root, root)
// Each query in O(log n * C) where C is the time DS process queries
// For custom queries/updates, call traversePath with custom lambda
// 1-Indexed
template<typename T = int>
struct HeavyLight{
    vector<int> depth, parent, subtree, chainHead, indexDS;
    bool valuesInEdges;
    int cnt = 1;

    HeavyLight(int n, bool valuesInEdges = false): depth(n), parent(n), subtree(n), chainHead(n), indexDS(n), valuesInEdges(valuesInEdges) {}
    
    template<class G>
    void dfs(const G &adjList, int u, int p = -1) {
        subtree[u] = 1;
        for(auto v: adjList[u]) {
            if( v == p ) continue;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(adjList, v, u);

            subtree[u] += subtree[v];
        }
    }

    template<class G>
    void buildHLD(const G &adjList, int u, int head, int p = -1) {
        chainHead[u] = head;
	    indexDS[u] = cnt++;

        int heavy = -1, sz_heavy = 0;
        for(auto v: adjList[u]){
            if(v == p) continue;
            if(sz_heavy < subtree[v]) heavy = v, sz_heavy = subtree[v];
        }

        if(heavy != -1) 
            buildHLD(adjList, heavy, head, u);

        for(auto v: adjList[u]) {
            if(v == p || v == heavy) continue;
            buildHLD(adjList, v, v, u);
        }	
    }

    template<class BinOperation>
    void traversePath(int u, int v, BinOperation op) {
        if(valuesInEdges && u == v) {
            op(indexDS[u], indexDS[u]);
            return;
        }

        for(; chainHead[u] != chainHead[v]; u = parent[ chainHead[u] ]){
            if( depth[ chainHead[u] ] < depth[ chainHead[v] ] ) swap(u, v);
            op(indexDS[chainHead[u]], indexDS[u]);
        }

        if(depth[u] > depth[v]) swap(u, v);
        
        if(valuesInEdges && u == v) return;
        op(indexDS[u] + valuesInEdges, indexDS[v]);
    }

    template<class DSType>
    T query(int u, int v, DSType *DS) {
        T ans = 0;
        traversePath(u, v, [this, &ans, DS](int l, int r) {
            ans += DS->query(l, r);
        });
        return ans;
    }

    template<class DSType>
    void update(int u, int v, T val, DSType *DS) {
        traversePath(u, v, [this, &val, DS](int l, int r) {
            DS->update(l, r, val);
        });
    }
};

template <typename T,typename S>
struct SegmentTreeItLazy{ // 0 - indexed
	T neutro = 0, neutro_lazy = 0;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;

    //S tipo de dato que recibe
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
		return a + b;
		//return a * b;
		//return __gcd(a, b);
		//return min(a, b);
	}
	void apply(int i, T val, int k){
		st[i] = val * k;
		if (i < size) delUp[i] = val, upd[i] = 1;
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
		push(l += size), push(r += size);
		T res = neutro;
		for (; l <= r; l >>= 1, r >>= 1){
			if (l & 1) res = merge(res, st[l++]);
			if (~r & 1) res = merge(res, st[r--]);
		}
		return res;
	}
	T& operator[](int i) { push(i+size); return st[i + size]; }
	T set(S x){
		return x;
	}
};



int main () {
	//fastIO();
	
	int n, q; cin>>n>>q;

    vector<vector<int>> adjList(n+1);
    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    HeavyLight<> *HLD = new HeavyLight<>(n+1);
    HLD->dfs(adjList, 1);
    HLD->buildHLD(adjList, 1, 1);
    
    SegmentTreeItLazy<lli, lli> *ST = new SegmentTreeItLazy<lli,lli>(n+1, 0);

    while(q--) {
        int a, b, c, d; cin>>a>>b>>c>>d;

        HLD->update(a, b, 1, ST);
        cout << HLD->query(c, d, ST) << endl;
        HLD->update(a, b, 0, ST);

    }


	return 0;
}

