#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)

using namespace std;


const int RED = 0, ORANGE = 1, YELLOW = 2, GREEN = 3, BLUE = 4, INDIGO = 5, VIOLET = 6, NO_COLOR = 7;
map< string, int > color_to_idx = {
    {"red", RED},
    {"orange", ORANGE},
    {"yellow", YELLOW},
    {"green", GREEN},
    {"blue", BLUE},
    {"indigo", INDIGO},
    {"violet", VIOLET},
};

const int MAX_COLORS = 8;


template <typename T,typename S>
struct SegmentTreeItLazy{ // 0 - indexed
	T neutro = 0, neutro_lazy = 0;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;

    //S tipo de dato que recibe
	SegmentTreeItLazy(int n, T val = 0){
		st.resize(2*n);
        fill(all(st), val);
		size = n;
		delUp.resize(n, neutro_lazy);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
		build();
	}

	T merge(T a, T b){
		return a + b;
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
};


template<typename T = int>
struct HeavyLight{
    vector<int> depth, parent, subtree, chainHead, indexDS;
    int cnt = 0;
    bool valuesInEdges = false;
    

    HeavyLight(int n, bool valuesInEdges = false): depth(n), parent(n), subtree(n), chainHead(n), indexDS(n), valuesInEdges(valuesInEdges){}
    
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
    T query(int u, int v, int color, vector<DSType*> &DS) {
        T ans = T();
        traversePath(u, v, [this, &ans, color, DS](int l, int r) {
            for(int i = 0; i < MAX_COLORS; i++){
                if(i == color) continue;
                ans += DS[i]->query(l, r);
            }
        });
        return ans;
    }

    template<class DSType>
    void update(int u, int v, int color, vector<DSType*> &DS) {
        traversePath(u, v, [this, color, DS](int l, int r) {
            for(int i = 0; i < MAX_COLORS; i++){
                if(i == color) continue;
                DS[i]->update(l, r, 0);
            }
            
            DS[color]->update(l, r, 1);
        });
    }
};




typedef SegmentTreeItLazy<int, int> SegTreeType;


int main () {
	fastIO();
	
	int n; cin>>n;

    vector< vector<int> > adjList(n);
    for(int i = 0; i < n-1; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector< SegmentTreeItLazy<int, int>* > SegTrees(MAX_COLORS);
    for(int i = 0; i < MAX_COLORS; i++) {
        SegTrees[i] = new SegTreeType(n, 0);
    } 
    SegTrees[NO_COLOR]->update(0, n-1, 1);
 
    HeavyLight<int> *HLD = new HeavyLight<int>(n, true);
    HLD->dfs(adjList, 0);
    HLD->buildHLD(adjList, 0, 0);


    vector<int> ans_all(MAX_COLORS);

    int q; cin>>q;
    while(q--){
        int u, v; cin>>u>>v;
        string color_input; cin>>color_input;
        int color = color_to_idx[color_input];

        int ans = HLD->query(u, v, color, SegTrees);
        ans_all[color] += ans;
        HLD->update(u, v, color, SegTrees);
    }

    for(auto color: {"red", "orange", "yellow", "green", "blue", "indigo", "violet"}){
        cout << color << " " << ans_all[ color_to_idx[color] ] << endl;
    }


	return 0;
}
 