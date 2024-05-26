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


const lli MOD = 998244353;


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
    	return (a + b) % MOD;
	}
	void build(){
		for(int i = size - 1; i; i--)
			st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void update(int i, T val) {
        i += size;
		for(st[i] = (st[i] + val) % MOD; i > 1; i >>= 1)
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



int main () {
	//fastIO();


    int n; cin>>n;
    vector<lli> nums(n+1);
    for(int i = 1; i <= n; i++)
        cin>>nums[i];


    auto nums_to_map = nums;
    sort(all(nums_to_map));

    nums_to_map.erase(unique(all(nums_to_map)), nums_to_map.end());


    auto mapping = [&](int n){
        return lower_bound(all(nums_to_map), n) - nums_to_map.begin();        
    };

    vector< SegmentTreeIt<lli,lli> *> STs(3);
    for(int i = 0; i < 3; i++) STs[i] = new SegmentTreeIt<lli,lli>(n+5, 0);

    vector<lli> dp(n+1);
    dp[n] = 0;

    STs[0]->update(mapping(  nums[n]  ), dp[n]);
    STs[1]->update(mapping(  nums[n]  ), 1);
    STs[2]->update(mapping(  nums[n]  ), nums[n] * (dp[n] + 1));

    for(int i = n-1; i >= 1; i--){
        auto num = nums[i];
        lli dps_lower   = STs[0]->query(0, mapping(num) - 1);
        lli dps_greater = STs[0]->query(mapping(num) + 1, n+2);

        lli how_many_lower   = STs[1]->query(0, mapping(num) - 1);
        lli how_many_greater = STs[1]->query(mapping(num) + 1, n+2);


        lli prod_lower   = STs[2]->query(0, mapping(num) - 1);
        lli prod_greater = STs[2]->query(mapping(num) + 1, n+2);


        dp[i] = num * (dps_lower - dps_greater) % MOD;
        dp[i] += num * (how_many_lower - how_many_greater) % MOD;
        
        if(dp[i] >= MOD) dp[i] -= MOD;

        dp[i] += prod_greater - prod_lower;

        if(dp[i] < 0) dp[i] += MOD;
        if(dp[i] >= MOD) dp[i] -= MOD;


        STs[0]->update(mapping(  num  ), dp[i]);
        STs[1]->update(mapping(  num  ), 1);
        STs[2]->update(mapping(  num  ), num * (dp[i] + 1));
    }


    lli ans = 0;
    for(int i = 1; i <= n; i++) 
        (ans += dp[i]) %= MOD;
    
    cout << ans << endl;


	return 0;
}

