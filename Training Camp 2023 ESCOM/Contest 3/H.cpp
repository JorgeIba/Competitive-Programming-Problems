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


int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

lli powerMod(lli a, lli b, lli mod){
	lli res = 1;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return res;
}


template<int p, int g, typename T>
void ntt(vector<T> & A, bool inv){ //O(n log n)
	int n = SZ(A);
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}

	vector<lli> wp(n>>1, 1);

	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, (inv?-1:1) * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = (wp[j - 1] * wk) % p;

		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = (A[i+j+k] * wp[j]) % p;
				A[i+j] = (u + v < p) ? u + v : u + v - p;
				A[i+j+k] = (u - v >= 0) ? u - v: u - v + p;
			}
		}
	}

	if(inv){
		lli inv_n = powerMod(n, p - 2, p);
		for(auto &x: A) x = (x*inv_n)%p;
	}
}
 
template<int p = 998244353, int g = 3, typename T>
vector<T> multiply(vector<T> A, vector<T> B){ //O(n logn) it uses NTT
	int sz = SZ(A) + SZ(B) - 1;
	int size = nearestPowerTwo(sz);
    
	A.resize(size), B.resize(size);
	ntt<p, g>(A, false); ntt<p, g>(B, false);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, true);

	A.resize(sz);
	return A;
}

const int MOD = 998244353;
const int MAXN = 2e6 + 100;

typedef vector<int> Poly;

Poly operator*(const Poly &A, const Poly &B) {
    return multiply(A, B);
}

Poly powerModP(Poly A, lli b){
    Poly R(1, 1);
    while(b){
        if(b&1) R = R * A;
        b >>= 1;
        A = A * A;
    }
    return R;
}


int main(){
    fastIO();

    int n, k; cin>>n>>k;

    vector<int> A(n);
    for(auto &x: A) cin>>x;

    vector<int> B(k);
    for(auto &x: B) cin>>x;


    int q; cin>>q;
    vector<int> Q(q);
    for(auto &x: Q) cin>>x;

    vector<int> ans(q);

    auto get_k_1 = [&](int b) {

        vector<int> a;
        for(auto x: A) {
            if(x < b) a.push_back(x);
        }

        vector<int> fr(MAXN);
        for(auto x: a) fr[x]++;

        lli D = 0, U = 0;
        forn(i, MAXN) {
            if(fr[i] >= 2) D++;
            else if(fr[i] == 1) U++;
        }

        Poly A = {1, 2};
        Poly B = {1, 2, 1};

        Poly C = powerModP(A, U) * powerModP(B, D);

        forn(i, q){
            int m = Q[i];
            int s = (m - 2*b - 2)/2;

            if(s < 0 || s >= SZ(C)) continue;

            ans[i] += C[s];
            if(ans[i] >= MOD) ans[i] -= MOD;
        }

    };

    for(auto b: B) {
        get_k_1(b);
    }

    for(auto x: ans) cout << x << endl;

    return 0;   
}