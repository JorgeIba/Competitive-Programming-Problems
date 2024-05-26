#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < n; i++)

using namespace std;

const lli INF = 1e15;
struct Node{
    pair<lli,int> mini = {INF, 0}, maxi = {-INF, 0};
    Node() {}
    Node(lli val, lli idx) {
        mini = {idx - val, idx};
        maxi = {idx + val, idx};
    }

    Node operator+(const Node &a) const {
        Node ans;
        ans.maxi = max(maxi, a.maxi);
        ans.mini = min(mini, a.mini);
        return ans;
    }
};


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
			forn(i,n) st[i+size] = set(v[i], i);
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
	T set(S x, int idx){
		return T(x, idx);
	}
	T& operator[](int i) { return st[i + size]; }
};



void main_(){
	
    lli n, a, b; cin>>n>>a>>b;
    a--, b--;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    SegmentTreeIt<Node, lli> *ST = new SegmentTreeIt<Node, lli>(n, Node(), nums);

    vector<int> dist(n, -1);
    
    queue<int> q;
    q.push(a);
    dist[a] = 0;

    ST->update(a, Node());

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        auto pu = nums[u];

        pair<lli,lli> v;
        int limit_l = max(u - pu, 0LL), limit_r = min(n-1, u + pu);


        while( u <= (v = ST->query(limit_l, u-1).maxi).first && dist[v.second] == -1) {
            dist[v.second] = dist[u] + 1;
            q.push(v.second);

            ST->update(v.second, Node());
        }

        while( (v = ST->query(u+1, limit_r).mini).first <= u && dist[v.second] == -1 ) {
            dist[v.second] = dist[u] + 1;
            q.push(v.second);

            ST->update(v.second, Node());
        }
    }

    cout << dist[b] << endl;

}




int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

