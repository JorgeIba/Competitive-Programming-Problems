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



vector< vector<int> > adjList;


vector< array<int, 2> > ranges;
vector<int> order;
int time_r = 1;


void dfs_euler(int u, int p = -1) {
    order.push_back(u);
    ranges[u][0] = time_r++;

    for(auto v: adjList[u]) {
        if(v == p) continue;
        dfs_euler(v, u);
    }

    ranges[u][1] = time_r - 1;
}





int main () {
	//fastIO();

    int n; cin>>n;

    adjList.resize(n+1);
    ranges.resize(n+1);

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    order.push_back(0);
    dfs_euler(1);


    // cout << "Order: " << endl;
    // for(auto u: order) cout << u << " ";
    // cout << endl << endl;

    // cout << "Ranges: " << endl;
    // for(int i = 1; i <= n; i++) {
    //     cout << i << ": " << ranges[i][0] << " - " << ranges[i][1] << endl;
    // }

    vector<ld> values(n+1);

    SegmentTreeIt<ld, ld> *ST = new SegmentTreeIt<ld, ld>(n+1, 0, values);

    // for(int i = 1; )



    int q; cin>>q;
    while(q--) {
        int t, x, y; cin>>t>>x>>y;
        if(t == 1) {
            int idx_x = ranges[x][0];
            ST->update(idx_x, log10l(y));
        } else {
            ld mult_x = ST->query(ranges[x][0], ranges[x][1]);
            ld mult_y = ST->query(ranges[y][0], ranges[y][1]);

            ld diff = mult_x - mult_y;
            // debugg(mult_x);
            // debugg(mult_y);

            if(diff < 9) {
                cout << fixed << setprecision(10) << powl(10, diff) << endl;
            } else {
                cout << 1000000000 << endl;
            }

        }
    }






	return 0;
}

