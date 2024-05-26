#include<bits/stdc++.h>

#define lli long long int
#define all(a) a.begin(), a.end()
#define SZ(a) (int)a.size() 
#define ld long double 
#define endl "\n"
#define fi first
#define se second
#define forn(i,n) for(int i = 0; i < n; i++)
#define fastIO() ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);

using namespace std;

vector< array<int, 2> > ranges_u;
vector<int> order;
int time_r = 0;

vector< vector<int> > adjList;
vector<int> nums;


void dfs_euler(int u, int p = -1) {
    order.push_back(u);
    ranges_u[u][0] = time_r++;

    for(auto v: adjList[u]) {
        if(v == p) continue;
        dfs_euler(v, u);
    }

    ranges_u[u][1] = time_r - 1;
}


const int maxM = 1010;


bitset<maxM> get_mask(int m) {

    vector< bool > is_prime(m, true);
    is_prime[0] = is_prime[1] = false;
    for(lli i = 2; i < m; i++) {
        for(lli j = 2; j*i < m; j++) {
            is_prime[i*j] = false;
        }
    }

    bitset<maxM> mask;
    for(int i = 0; i < m; i++) {
        mask[i] = is_prime[i];
    }

    return mask;
}

bitset< maxM > prefix_m;

struct Node{
    bitset<maxM> frqs;
    int sz;

    Node() {}
    Node(int sz, int u): sz(sz){
        frqs[u] = 1;
    }

    void apply_shift(int m) {
        m %= sz;
        bitset<maxM> left_part, right_part;

        right_part = frqs << m;
        left_part = frqs >> (sz - m);

        frqs = (left_part | right_part) & prefix_m;
    }

    Node operator+(const Node &a) const{
        Node ans;
        ans.sz = sz;
        ans.frqs = frqs | a.frqs; 
        return ans;
    }

};

template <typename T,typename S>
struct SegmentTreeItLazy{ // 0 - indexed
	T neutro = T();
    int neutro_lazy = 0;
	int size, height;
    int m;
	vector<T> st;
    vector<int> delUp;
	vector<bool> upd;

    //S tipo de dato que recibe
	SegmentTreeItLazy(int n, int m, T val = T(),  const vector<S> &v = vector<S>()): m(m){
		st.resize(2*n);
        if(v.empty()) fill(all(st), val);
		size = n;
		delUp.resize(n, neutro_lazy);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
        if(!v.empty()) forn(i,n) st[i+size] = set(v[i], m);
		build();
	}

	T merge(T a, T b){
		return a + b;
		//return a * b;
		//return __gcd(a, b);
		//return min(a, b);
	}
	void apply(int i, int val, int k){
		st[i].apply_shift(val);
		if (i < size) delUp[i] = (delUp[i] + val) % m, upd[i] = 1;
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
	void update(int l, int r, int val){
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
	T set(S x, int m){
		return T(m, x);
	}
};



int main() {
    fastIO();

    int n, m; cin>>n>>m;

    for(int i = 0; i < m; i++)
        prefix_m.set(i);    


    adjList.resize(n);
    nums.resize(n);
    ranges_u.resize(n);
    for(int i = 0; i < n; i++) {
        cin>>nums[i];
        nums[i] %= m;
    }

    for(int i = 1; i <= n-1; i++) {
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs_euler(0);
    bitset<maxM> mask_primes = get_mask(m);

    vector<int> numbers_euler_order(n);
    for(int i = 0; i < n; i++) {
        numbers_euler_order[i] = nums[ order[i] ];
    }


    SegmentTreeItLazy<Node, int> *ST = new SegmentTreeItLazy<Node, int>(n, m, Node(), numbers_euler_order);


    int q; cin>>q;

    while(q--) {
        int t; cin>>t;
        if(t == 1) {
            int v, x; cin>>v>>x; v--;
            ST->update(ranges_u[v][0], ranges_u[v][1], x);
        } else {
            int v; cin>>v; v--;
            bitset<maxM> ans = mask_primes & ST->query(ranges_u[v][0], ranges_u[v][1]).frqs;

            cout << ans.count() << endl;

        }
    }

    return 0;
}