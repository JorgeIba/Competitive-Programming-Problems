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


typedef vector<int> Poly;

const int MOD = 998244353;
const int MAXN = 1e5 + 1000;

int fact[MAXN], invFact[MAXN];

void prec(){
    
    fact[0] = fact[1] = invFact[0] = invFact[1] = 1;

    for(int i = 2; i < MAXN; i++){
        fact[i] = 1LL * i * fact[i-1] % MOD;
        invFact[i] = powerMod(fact[i], MOD-2, MOD);
    }
}


int main () {
	//fastIO();

    prec();

	
    int n, k; cin>>n>>k;
    
    Poly T(n+1), P(n+1);
    for(auto &x: T) cin>>x;
    for(auto &x: P) cin>>x;

    for(auto &x: T) 
        if(x < 0)
            x += MOD;

    for(auto &x: P) 
        if(x < 0)
            x += MOD;

    if(k == 0){
        for(int i = 0; i <= n; i++){
            cout << (T[i] + P[i]) % MOD << " ";
        }
        cout << endl;
        return 0;
    }


    if(k < 0) k += MOD;
    int inv_k = powerMod(k, MOD-2, MOD);


    vector<int> pot_k(n+1, 1), pot_mk(n+1, 1), pot_inv_k(n+1, 1), pot_inv_mk(n+1, 1);
    forr(i, 1, n){
        pot_k[i] = 1LL * k * pot_k[i-1] % MOD;
        pot_mk[i] = 1LL * (MOD - k) * pot_mk[i-1] % MOD;
        pot_inv_k[i] = 1LL * inv_k * pot_inv_k[i-1] % MOD;
        pot_inv_mk[i] = 1LL * (MOD - inv_k) * pot_inv_mk[i-1] % MOD;
    }


    Poly Q(n+1);
    for(int i = 0; i <= n; i++){
        Q[i] = invFact[i];
    }
    reverse(all(Q));

    forr(i, 0, n){
        T[i] = 1LL * T[i] * fact[i] % MOD * pot_k[i] % MOD;
    }

    forr(i, 0, n){
        P[i] = 1LL * P[i] * fact[i] % MOD * pot_mk[i] % MOD;
    }

    auto TQ = multiply(T, Q);
    auto PQ = multiply(P, Q);


    vector< int > ans_t(n+1), ans_p(n+1);


    forr(j, 0, n){
        ans_t[j] = 1LL * pot_inv_k[j]  * invFact[j] % MOD * TQ[n + j]  % MOD;
    }

    forr(j, 0, n){
        ans_p[j] = 1LL * pot_inv_mk[j] * invFact[j] % MOD * PQ[n + j] % MOD;
    }
    
    for(int i = 0; i <= n; i++){
        lli ans = (ans_t[i] + ans_p[i]) % MOD;
        cout << ans << " ";
    }
    cout << endl;

	return 0;
}

