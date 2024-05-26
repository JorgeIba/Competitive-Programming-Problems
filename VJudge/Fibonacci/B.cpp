#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

template<int sqr=5,int mod=1'000'000'000+7>
struct Ext{
    lli a, b;

    Ext(): a(0), b(0) {}
    Ext(lli a, lli b=0): a(a), b(b) {}

    Ext operator*(const Ext &A) const {
        lli new_a = (a * A.a % mod + sqr * b % mod * A.b % mod) % mod;
        lli new_b = (a * A.b % mod + b * A.a % mod) % mod;

        return {new_a, new_b};
    }

    Ext operator+(const Ext &A) const{ return {(a + A.a) % mod, (b + A.b) % mod}; }
    Ext operator-(const Ext &A) const{ return {(a - A.a + mod) % mod, (b - A.b + mod) % mod};}
    Ext operator*(const lli k) const{ return {a * k % mod, b * k % mod}; }
    bool operator==(const Ext &A) const{ return a == A.a && b == A.b; }
    bool operator!=(const Ext &A) const{ return !(*this == A); }

    Ext power(lli k) const {
        Ext res = Ext(1, 0);
        for(auto A = *this; k; k >>= 1, A = A * A){
            if(k&1) res = res * A;
        } 
        return res;
    }

    Ext conj() const {
        return {a, mod - b};
    }

    Ext inv() const {
        lli den = a*a%mod - sqr*b%mod*b%mod;
        if(den < 0) den += mod;
        return conj() * powerMod(den, mod-2, mod);
    }
};

template <typename T,typename S>
struct SegmentTreeItLazy{
	T neutro = 0, neutro_lazy = Ext(1,0);
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;

	SegmentTreeItLazy(int n, T val = 0,  const vector<S> &v = vector<S>()){
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
		return a + b;
	}

	void apply(int i, T val, int k){
        st[i] = st[i] * val;
		if (i < size) delUp[i] = delUp[i] * val, upd[i] = 1;
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
                T ansL = neutro;
        	T ansR = neutro;
                push(l += size);
                push(r += size);
                for (; l <= r; l >>= 1, r >>= 1){
                        if (l & 1) ansL = merge(ansL, st[l++]);
                        if (~r & 1) ansR = merge(st[r--], ansR);
                }
                return merge(ansL, ansR);
        }
	T& operator[](int i) { push(i+size); return st[i + size]; }
	T set(S x){
		return x;
	}
};


const int MOD = 1e9+7;
int main () {
	fastIO();
    const int inv_2 = (MOD+1)/2;

    Ext phi(inv_2, inv_2), rho = phi.conj();
	Ext sqr5(0, 1);
	Ext inv_5 = sqr5.inv();


	int n, q; cin>>n>>q;

	vector<int> init(n);
	for(auto &x: init) cin>>x;

	vector<Ext<5, MOD>> phis(n), rhos(n);
	for(int i = 0; i < n; i++){
		auto x = init[i];
		phis[i] = phi.power(x);
		rhos[i] = rho.power(x);
	}

	SegmentTreeItLazy<Ext<5,MOD>, Ext<5,MOD>> ST_phi(n, Ext(), phis);
	SegmentTreeItLazy<Ext<5,MOD>, Ext<5,MOD>> ST_rho(n, Ext(), rhos);


	while(q--){
		int t, l, r; cin>>t>>l>>r; l--, r--;

		if(t == 1){
			int x; cin>>x;
			ST_phi.update(l, r, phi.power(x));
			ST_rho.update(l, r, rho.power(x));
		} else {
			auto ans = (ST_phi.query(l, r) - ST_rho.query(l, r)) * inv_5;
			cout << ans.a << endl;
		}
	}


	return 0;
}

