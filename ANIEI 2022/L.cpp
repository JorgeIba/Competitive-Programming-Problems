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



const lli maxN = 1e5+100;
vector<lli> totalP(maxN+1);
vector<lli> primes;
void prec() {
    for(lli i = 2; i <= maxN; i++) {
        if(!totalP[i]) {
            primes.push_back(i);
            for(lli j = 1; j*i <= maxN; j++) {
                totalP[i*j]++;
            }
        }
    }
}


struct Q{
    lli n, k, i;
    Q() {}
    Q(lli n, lli k, lli i): n(n), k(k), i(i) {}
};

int main () {
	fastIO();

    prec();

    lli n; cin>>n;
    vector< Q > queries(n);
    for(int i = 0; i < n; i++) {
        lli n, k; cin>>n>>k;
        queries[i] = Q(n, k, i);
    }

    vector<vector<Q>> reub(SZ(primes));
    for(int i = 0; i < n; i++) {
        auto q = queries[i];
        lli k_prime = (prev(upper_bound(all(primes), q.k)) - primes.begin());

        reub[k_prime].push_back(q);
    }

    
    SegmentTreeIt<lli,lli> *ST = new SegmentTreeIt<lli,lli>(maxN, 0);

    vector<lli> marks(maxN+1);

    vector<lli> ans(n);

    for(int i = 0; i < SZ(primes); i++) {
        lli p = primes[i];
        for(lli j = 1; j*p <= maxN; j++) {
            marks[p*j]++;
            if(marks[p*j] == totalP[p*j]) {
                ST->update(p*j, 1);
            }
        }

        for(auto q: reub[i]) {
            ans[q.i] = ST->query(2, q.n);
        }
    }

    for(auto x: ans) cout << x << endl;


	return 0;
}

