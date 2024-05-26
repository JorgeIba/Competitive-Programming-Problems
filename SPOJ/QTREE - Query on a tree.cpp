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

const int INF = 1e9;


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
        T ans = -INF;
        traversePath(u, v, [this, &ans, DS](int l, int r) {
            ans = max(ans, DS->query(l, r));
        });
        return ans;
    }

    template<class DSType>
    void update(int u, int v, T val, DSType *DS) {
        traversePath(u, v, [this, &val, DS](int l, int r) {
            DS->update(l, val);
        });
    }
};

// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = -INF;
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
    	return max(a, b);
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





void main_(){
	int n; cin>>n;

    vector< vector<int> > adjList(n+1);

    vector<tuple<int,int,int>> edges;
    for(int i = 0; i < n-1; i++) {
        int u, v, c; cin>>u>>v>>c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edges.push_back({u, v, c});
    }


    HeavyLight<int> *HLD = new HeavyLight<int>(n+1, true);
    HLD->dfs(adjList, 1);
    HLD->buildHLD(adjList, 1, 1);



    vector<int> values(n+1, -INF);
    for(auto e: edges) {
        auto [u, v, c] = e;
        if(HLD->parent[u] != v) swap(u, v);

        values[  HLD->indexDS[u]  ] = c;
    }


    SegmentTreeIt<int,int> *ST = new SegmentTreeIt<int,int>(n+1, -INF, values);

    while(true) {
        string t; cin>>t;
        if( t == "DONE") break;
    
        if(t == "QUERY") {
            int u, v; cin>>u>>v;

            if(u == v) {
                cout << 0 << endl;
                continue;
            }

            cout << HLD->query(u, v, ST) << endl;
            
        } else {
            int idx, val; cin>>idx>>val;
            idx--;

            auto [u, v, c] = edges[idx];

            if(HLD->parent[u] != v) swap(u, v);


            HLD->update(u, u, val, ST);
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

