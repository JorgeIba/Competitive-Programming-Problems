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

const lli MOD = 1e9+7;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a % MOD;
        b>>=1;
        a = a*a %MOD;
    }
    return res;
}

template <typename T,typename S> 
struct ST_Product{ // 0 - indexed
	T neutro = 1, neutro_lazy = 1;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;
    
    //S tipo de dato que recibe
	ST_Product(int n, T val = 1,  const vector<S> &v = vector<S>()){
		st.resize(2*n);
        if(v.empty()) fill(all(st), val);
		size = n;
		delUp.resize(n, neutro_lazy);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
        if(!v.empty()) forn(i,n) st[i+size] = set(v[i]);
		build();
	}

	T merge(T a, T b){
		return a * b % MOD;
	}
	void apply(int i, T val, int k){
        st[i] = st[i] * binPow(val, k) % MOD; 
		if (i < size) delUp[i] = delUp[i]*val%MOD, upd[i] = 1;
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
				upd[i] = 0, delUp[i] = neutro_lazy; //Neutro of lazy
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
	T& operator[](int i) { return st[i + size]; }
	T set(S x){
		return x;
	}
};


template <typename T,typename S> 
struct ST_Or{ // 0 - indexed
	T neutro = 0;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;
    
    //S tipo de dato que recibe
	ST_Or(int n, T val = 0,  const vector<S> &v = vector<S>()){
		st.resize(2*n+1);
        if(v.empty()) fill(all(st), val);
		size = n;
		delUp.resize(n);
		upd.resize(n);
		height = sizeof(int) * 8 - __builtin_clz(size);
        if(!v.empty()) forn(i,n) st[i+size] = set(v[i]);
		build();
	}

	T merge(T a, T b){
		return a | b;
	}
	void apply(int i, T val, int k){
		st[i] |= val; 
		if (i < size) delUp[i] |= val, upd[i] = 1;
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
				upd[i] = 0, delUp[i] = 0;
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
	T& operator[](int i) { return st[i + size]; }
	T set(S x){
		return x;
	}
};


const lli maxA = 301;
lli mask[maxA];

vector<lli> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 
211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
lli sz_primes = SZ(primes);

vector<lli> invPrimes(sz_primes);

void init()
{
    for(int i = 0; i<sz_primes; i++) invPrimes[i] = binPow(primes[i], MOD-2);
    for(int i = 2; i<maxA; i++)
    {
        for(int j = 0; j<sz_primes; j++)
        {
            if(i % primes[j] == 0) mask[i] |= (1LL<<j);
        }
    }
}

lli get_factor(lli mask_primes)
{
    lli ans = 1;
    for(int i = 0; i<sz_primes; i++)
    {
        if(!(mask_primes & (1LL << i))) continue;
        ans = ans*(primes[i] - 1) % MOD * invPrimes[i] % MOD;
    }
    return ans;
}


int main () {
	fastIO();
    init();

    lli n, q; cin>>n>>q;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    ST_Product<lli,lli> Product(n, 1, nums);

    ST_Or<lli,lli> Or(n);
    for(int i = 0; i<n; i++) Or.update(i, i,  mask[nums[i]]);

    
    while(q--)
    {
        string type_q; cin>>type_q;
        lli l, r; cin>>l>>r; l--, r--;
        if(type_q == "MULTIPLY")
        {
            lli x; cin>>x;
            Product.update(l, r, x);
            Or.update(l, r, mask[x]);
        }
        else
        {
            lli first_part = Product.query(l, r);

            lli mask_primes = Or.query(l, r);

            cout << first_part * get_factor(mask_primes) % MOD << endl;

        }
        
    }
    
	return 0;
}