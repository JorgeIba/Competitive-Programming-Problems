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


int nearestPowerTwo(int n){
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
void ntt(vector<T> & A, bool inv){
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
vector<T> multiply(vector<T> A, vector<T> B){ 
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

const int MAXN = 1e6+1000;
const int MOD  = 998244353;
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec(){
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

int main () {
	//fastIO();
    prec();

    int n; cin>>n;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<int> fr(30);
    for(auto x: nums){
        for(int i = 0; i < 30; i++) {
            if(x & (1 << i)) {
                fr[i]++;
            }
        }
    }

    auto solve = [&](int bit) {
        vector<int> ones(n+1), zeros(n+1);

        for(int i = 1; i <= n; i+=2) {
            ones[i]  = nCr(fr[bit], i);
        }

        for(int i = 0; i <= n; i++){
            zeros[i] = nCr(n - fr[bit], i);
        }

        auto C = multiply(ones, zeros);
        return C;
    };

    vector<int> ans(n+1);

    for(int i = 0; i < 30; i++) {
        auto ways = solve(i);

        for(int j = 0; j <= n; j++){
            ans[j] += 1LL*(1LL << i) * ways[j] % MOD;
            if(ans[j] >= MOD) ans[j] -= MOD;
        }
    }

    for(int i = 1; i <= n; i++) {
        ans[i] = (ans[i-1] + ans[i]) % MOD;
    }

    int q; cin>>q;
    while(q--) {
        int m; cin>>m;

        cout << ans[m] << endl;
    }

	return 0;
}

