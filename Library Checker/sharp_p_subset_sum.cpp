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

lli p = 998244353;
const lli MOD = p;
const lli maxK = 5e5+10;

const lli maxN = 1e7;
vector<lli> inv(maxN+1, 1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
}


template<typename T> //Returns 1 / F, with d coeffs
vector<T> invert(vector<T> F, int d=-1) 
{
	if(d==-1) d = SZ(F);
    vector<T> R_n = { powerMod(F[0], p-2, p) }; //equivalent to: 1 / F[0]
    while(SZ(R_n) <= d)
    {
        int j = 2*SZ(R_n);
        auto FF = F; FF.resize(j);
        vector<T> RnF = multiply(R_n, FF);
        for(auto &x: RnF) x = p-x;
        RnF[0] = RnF[0] + 2 < p? RnF[0] + 2: RnF[0] + 2 - p; 
        R_n = multiply(R_n, RnF);
        R_n.resize(j);
    }
    R_n.resize(d+1);
    return R_n;
}

template<typename T>
vector<T> derivate(const vector<T> &A){
	int n = SZ(A);
	vector<T> ans(n-1);
	for(int i = 1; i<n; i++)
	{
		ans[i-1] = (A[i]*i)%p;
	}
	return ans;
}

template<typename T>
vector<T> integrate(const vector<T> &P){
	vector<T> A(SZ(P) + 1);
	for(int i = 1; i<=SZ(P); i++)
		A[i] = (P[i-1] * inv[i])%p;
	return A;
}

template<typename T>
vector<T> logn(const vector<T> &P){
	assert(P[0] == 1);
	int n = SZ(P);
	vector<T> A = integrate( multiply(derivate(P), invert(P)) );
	A.resize(n);
	return A;
}

template<typename T>
vector<T> exp(const vector<T> &P, int d = -1){ //E(x) = E(x)(1-ln(E(x))+A(x))
	if(d == -1) d = SZ(P);
	assert(P[0] == 0);
	vector<T> E(1,1);
	while(SZ(E) < d){
		int c = 2*SZ(E);
		E.resize(c);
		vector<T> S = logn(E);
		for(int i = 0; i<min(SZ(P),SZ(S)); i++)
		{
			S[i] = (P[i] - S[i] + p) % p;
		}
		S[0] = 1;
		E = multiply(E, S);
		E.resize(c);
	}
	E.resize(d);
	return E;
}



int main () {
	fastIO();
	prec();
    int n, t; cin>> n >> t;
	
	vector<lli> fr(maxK);
	for(int i = 0; i<n; i++)
	{
		lli x; cin>>x; fr[x]++;
	}

	vector<lli> P(t+1);
	for(lli j = 1; j<=t; j++)
	{
		for(lli i = 1; i*j <= t; i++)
		{
			P[i*j] += fr[i] * inv[j] % MOD * (j & 1 ? 1 : MOD-1) % MOD;
			if(P[i*j] >= MOD) P[i*j] -= MOD;
		}
	}
	
	P = exp(P);
	for(int i = 1; i<=t; i++)
	{
		cout << P[i] << " ";
	}
	

	return 0;
}