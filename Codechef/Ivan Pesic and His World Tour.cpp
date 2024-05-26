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
    	return a ^ b;
	}
	void build(){
		for(int i = size - 1; i; i--)
			st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void update(int i, T val) {
		for(st[i += size] = val; i > 1; i >>= 1)
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

template<typename T = int>
struct HeavyLight{
    vector<int> depth, parent, subtree, chainHead, indexDS;
    bool valuesInEdges = false;
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

    template<class BinaryOperation>
    void traversePath(int u, int v, BinaryOperation op) {
        // if(valuesInEdges && u == v) {
        //     op(indexDS[u], indexDS[u]);
        //     return;
        // }

        for(; chainHead[u] != chainHead[v]; u = parent[ chainHead[u] ]){
            if( depth[ chainHead[u] ] < depth[ chainHead[v] ] ) swap(u, v);
            op(indexDS[chainHead[u]], indexDS[u]);
        }

        if(depth[u] > depth[v]) swap(u, v);
        
        // if(valuesInEdges && u == v) return;
        op(indexDS[u] + valuesInEdges, indexDS[v]);
    }

    template<class DSType>
    pair<T, int> query(int u, int v, DSType *DS) {
        T ans = T();
        int length_path = 0;
        traversePath(u, v, [this, &ans, &length_path, DS](int l, int r) {
            length_path += (r - l + 1);
            ans ^= DS->query(l, r);
        });
        return {ans, length_path};
    }

    template<class DSType>
    void update(int u, int v, T val, DSType *DS) {
        traversePath(u, v, [this, &val, DS](int l, int r) {
            DS->update(l, val);
        });
    }
};



mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define ull unsigned long long int
ull get_random() {
    uniform_int_distribution<ull> dist(1, 1ULL - 1);
    return dist(rng);
}

void main_(){
    int n, q; cin>>n>>q;

    vector<ull> nums(n+1, 0);
    for(int i = 1; i <= n; i++) cin>>nums[i];


    vector<vector<int>> adjList(n+1);
    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<ull> random_xors(n+1);
    for(auto &x: random_xors) x = get_random();
    SegmentTreeIt<ull, ull> *ST_check = new SegmentTreeIt<ull, ull>(n+1, 0, random_xors);

    for(auto &x: nums) {
        x = random_xors[x];
    }

    HeavyLight<ull> *HLD = new HeavyLight<ull>(n+1);
    HLD->dfs(adjList, 1);
    HLD->buildHLD(adjList, 1, 1);

    vector<ull> values(n+1);
    for(int i = 1; i <= n; i++) {
        values[HLD->indexDS[i]] = nums[i];
    }

    SegmentTreeIt<ull,ull>  *ST_tree = new SegmentTreeIt<ull,ull>(n+1, 0, values);

    while (q--){
        int t, x, y; cin>>t>>x>>y;
        if(t == 1){
            auto [xor_path, length_path] = HLD->query(x, y, ST_tree);
            ull xor_prefix = ST_check->query(1, length_path);

            cout << (xor_path == xor_prefix ? "Yes" : "No") << endl; 

        } else {
            HLD->update(x, x, random_xors[y], ST_tree);
        }
    }
	
}


int main () {
	fastIO();

	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

