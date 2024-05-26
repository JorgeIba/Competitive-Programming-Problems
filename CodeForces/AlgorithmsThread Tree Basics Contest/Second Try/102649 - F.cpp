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
		for(st[i += size] += val; i > 1; i >>= 1)
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



vector< vector<int> > adjList;
vector<int> order, parent;
vector< array<int, 2> > ranges;
int time_r = 1;


void dfs_euler(int u, int p = -1) {

    parent[u] = p;

    order.push_back(u);
    ranges[u][0] = time_r++;

    for(auto v: adjList[u]) {
        if(v == p) continue;

        dfs_euler(v, u);
    }

    ranges[u][1] = time_r-1;
}



void main_() {
    int n, q; cin>>n>>q;

    time_r = 1;

    adjList.clear();
    adjList.resize(n+1);

    ranges.clear();
    ranges.resize(n+1);

    order.clear();

    parent.clear();
    parent.resize(n+1);

    

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }    

    order.push_back(0);

    dfs_euler(1);


    SegmentTreeIt<lli,lli> *ST = new SegmentTreeIt<lli,lli>(n+1, 0);

    while(q--) {
        int a, b, x; cin>>a>>b>>x;

        if(x == 0) {
            if(parent[a] != b) swap(a, b);
            assert(parent[a] == b);

            cout << abs(ST->query(ranges[a][0], ranges[a][1])) << endl;
        } else {

            ST->update(ranges[a][0], x);
            ST->update(ranges[b][0], -x);
        }

    }


}



int main () {
	fastIO();
    int t; cin>>t;

    while(t--) main_();

	return 0;
}

