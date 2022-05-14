#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

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



int main () {
	//fastIO();

    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums){
         cin>>x;
    }


    map<lli,lli> num_to_map, map_to_num;
    int id = 1;

    auto copy_nums = nums; sort(all(copy_nums));

    for(auto x: copy_nums) {
        if(!num_to_map.count(x)) {
            num_to_map[x] = id;
            map_to_num[id++] = x;
        }
    }


    for(auto &x: nums){
        x = num_to_map[x];
    }

    SegmentTreeIt<lli,lli> *ST = new SegmentTreeIt<lli,lli>(id+2, 0);


    for(auto x: nums) ST->update(x, 1);
    

    for(auto x: nums) {
        lli greater = ST->query(x+1, id+1);
        lli equal = ST->query(x, x) ;
        lli lower = ST->query(0, x-1);


        // cout << x << " - " << id+1 << " " << greater << endl;
        // cout << x << " " << lower << " " << equal << " " << greater << endl;

        ld lose = (ld)greater / n;
        ld draw = (ld)equal / n;
        ld win = (ld)lower / n;
        cout << fixed << setprecision(10) << lose << " " << draw << " " << win << endl;
    }



	return 0;
}

