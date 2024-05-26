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
				lli u = A[i + j], v = (A[i+j+k] * wp[j]) % p;
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


const lli MOD = 1'699'741'697;
const lli p = MOD;
 
template<int p = MOD, int g = 3, typename T>
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


typedef vector<lli> Poly;

const int MAXN = 2e5+1000;

Poly operator*(const Poly A, const Poly B) {
    auto C = multiply(A, B);
    C.resize(  min(SZ(C), MAXN)  );
    return C;
}


void normalize(Poly &P) {
    while(SZ(P) > 1 && !P.back()) P.pop_back();
}


Poly operator-(const Poly P, const Poly A) {
    Poly ans( max(SZ(P), SZ(A)) );
    for(int i = 0; i < SZ(ans); i++) {
        lli a = 0, b = 0;
        if(i < SZ(P)) a = P[i];
        if(i < SZ(A)) b = A[i];
        ans[i] = (a - b) % MOD;
        if(ans[i] < 0) ans[i] += MOD;
    }
    normalize(ans);
    return ans;
}



lli inv(lli n){
    return powerMod(n, p-2, p);
}


Poly invert(const Poly P, int d = -1) {
    if(d == -1) d = SZ(P);
    Poly R_n = vector{  inv(P[0])  };
    while(SZ(R_n) <= d) {
        int j = 2 * SZ(R_n);
        Poly FF = P; FF.resize(j);
        Poly RnF = R_n * FF;
        for(auto &x: RnF) x = (MOD - x);
        RnF[0] = (RnF[0] + 2) % MOD;
        R_n = R_n * RnF;
        R_n.resize(j);
    }

    R_n.resize(d+1);
    return R_n;
}




Poly derivate(const Poly P) {
    int n = SZ(P);
    Poly ans(n-1);
    for(int i = 1; i < n; i++) {
        ans[i-1] = P[i] * i % MOD;
    }
    return ans;
}


Poly integrate(const Poly P){
    Poly A(SZ(P) + 1);
    for(int i = 1; i <= SZ(P); i++) {
        A[i] = P[i-1] * inv(i) % MOD;
    }
    return A;
}

Poly logn(const Poly P) {
    assert(P[0] == 1);
    int n = SZ(P);
    Poly A = integrate(derivate(P) * invert(P));
    A.resize(n);
    return A;
}


Poly exp(const Poly P, int d = -1) {
    if(d == -1) d = SZ(P);
    assert(P[0] == 0);
    Poly E(1, 1);
    while(SZ(E) <= d+1) {
        int c = 2*SZ(E);
        E.resize(c);
        Poly S = logn(E);
        S = P - S;
        S[0] = 1;
        E = E * S;
        E.resize(c);
    }
    E.resize(d+1);
    return E;
}

const lli maxN = 5e5;
vector<lli> fact(maxN+1, 1), inv_n(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i <= maxN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv_n[i] = MOD - (MOD/i)*inv_n[MOD%i]%MOD;
        invFact[i] = inv_n[i]*invFact[i-1]%MOD;
    }
}

int main () {
	fastIO();

    prec();

    int N, K; cin>>N>>K;

    Poly x = {0, 1};

    Poly e_x_k = exp(x, K);
    Poly e_x = exp(x, N);

    auto A = e_x_k * e_x;

    auto h = [&](int i) {
        return A[i] * fact[i] % MOD;
    };


    vector<lli> g(N+1);
    g[0] = 1;
    for(int n = 1; n <= N; n++) {
        g[n] = g[n-1] * h(n-1) % MOD;
    }

    // for(auto x: g) cout << x << " ";

    Poly G = g;
    for(int n = 0; n <= N; n++) 
        G[n] = G[n] * invFact[n] % MOD;


    auto F = logn(G);

    lli ans = F[N];

    cout << ans * fact[N] % MOD << endl;


	return 0;
}

