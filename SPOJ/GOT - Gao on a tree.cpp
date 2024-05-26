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
    T query(int u, int v, int c, DSType *DS) {
        T ans = T();
        traversePath(u, v, [this, &ans, c, DS](int l, int r) {
            ans += DS->equalTo(l, r, c);
        });
        return ans;
    }
};

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;
	vector<int> pref; //just use this if you want sums

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<lli>::iterator from, vector<lli>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		pref.reserve(to - from + 1);
		pref.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
			pref.push_back(pref.back() + *it);
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	//number of elements equal to k in [l, r]
	int equalTo(int l, int r, int k){
		if(l > r || k < lo || k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		int m = (lo + hi) / 2;
		if(k <= m) return left->equalTo(lb + 1, rb, k);
		else return right->equalTo(l - lb, r - rb, k);
	}
};


int main () {
	//fastIO();
	
	int n, q; 

    while(cin>>n>>q) {
        vector<lli> nums(n);
        for(auto &x: nums) cin>>x;

        vector< vector<int> > adjList(n+1);
        for(int i = 1; i < n; i++) {
            int u, v; cin>>u>>v;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        HeavyLight<lli> *HLD = new HeavyLight<lli>(n+1);
        HLD->dfs(adjList, 1);
        HLD->buildHLD(adjList, 1, 1);

        vector<lli> values(n);
        for(int i = 1; i <= n; i++) {
            values[ HLD->indexDS[i] - 1 ] = nums[i-1];
        }

        WaveletTree *WT = new WaveletTree(all(values), *min_element(all(values)), *max_element(all(values)));

        while(q--){
            int u, v, c; cin>>u>>v>>c;
            int how_many = HLD->query(u, v, c, WT);
            cout << (how_many ? "Find" : "NotFind") << endl;
        }



    }

	return 0;
}

