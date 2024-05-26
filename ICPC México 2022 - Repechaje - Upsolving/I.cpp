#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector<int> nums, first_left, first_right;
int n; 
const int INF = 1e9+10;

void prec_left(){
    stack<pair<int,int>> s;
    s.push({INF, 0});
    for(int i = 1; i <= n; i++) {
        auto num = nums[i];
        while(!s.empty() && s.top().first < num)
            s.pop();

        first_left[i] = s.top().second;

        s.push({num, i});
    }
}

void prec_right(){
    stack<pair<int,int>> s;
    s.push({INF, n+1});
    for(int i = n; i >= 1; i--) {
        auto num = nums[i];
        while(!s.empty() && s.top().first <= num)
            s.pop();

        first_right[i] = s.top().second;

        s.push({num, i});
    }
}


struct Node{
    int num=0, idx=0;
    Node(){}
    Node(int num, int idx): num(num), idx(idx) {}

    Node operator+(const Node &b) {
        Node c;
        if(num < b.num) {
            c.num = b.num;
            c.idx = b.idx;
        } else {
            c.num = num;
            c.idx = idx;
        }
        return c;
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
			for(int i = 0; i < n; i++) st[i+size] = set(v[i], i);
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
	T set(S x, int i){
		return T(x, i);
	}
	T& operator[](int i) { return st[i + size]; }
};



int main () {
	fastIO();

    cin>>n;
    nums.resize(n+1);
    first_left.resize(n+1);
    first_right.resize(n+1);
    
    for(int i = 1; i <= n; i++) cin>>nums[i];


    SegmentTreeIt<Node, int> *ST = new SegmentTreeIt<Node, int>(n+1, Node(), nums);
    prec_left();
    prec_right();

    int q; cin>>q;

    while(q--){
        int m; cin>>m;
        vector<int> indices(m);
        for(auto &x: indices) cin>>x;

        lli ans = 0;
        for(int i = 0; i < m; i++){
            auto index = indices[i];
            int left = first_left[index];
            int right = first_right[index];

            int valid_left = upper_bound(all(indices), left) - indices.begin();
            int valid_right = prev(lower_bound(all(indices), right)) - indices.begin();

            // cout << index << " -> " << valid_left
            ans += 1LL * nums[index] * (i - valid_left + 1) * (valid_right - i + 1);
        }


        for(int i = 0; i < m-1; i++){
            auto index_l = indices[i];
            auto index_r = indices[i+1];

            if(index_l + 1 > index_r - 1) continue;

            auto mx = ST->query(index_l+1, index_r-1);

            int left = first_left[mx.idx];
            int right = first_right[mx.idx];

            int valid_left = upper_bound(all(indices), left) - indices.begin();
            int valid_right = prev(lower_bound(all(indices), right)) - indices.begin();


            ans += 1LL * mx.num * (i - valid_left + 1) * (valid_right - (i+1) + 1);
        }
        cout << ans << endl;
    }



	return 0;
}

