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

lli n, k, mul; 
const lli MOD = 1e9+7;


int nearestPowerOfTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}


template<lli p, lli g>
void ntt(vector<lli> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, inv * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = powerMod(n, p - 2, p);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p;
	}
}

template<lli p, lli g>
vector<lli> convolution(vector<lli> A, vector<lli> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
    A.resize(sz);
	return A;
}

const lli a = 998244353, b = 985661441, c = 754974721;
const lli a_b = powerMod(a, b-2, b), a_c = powerMod(a, c-2, c), b_c = powerMod(b, c-2, c);
vector<lli> multiply(const vector<lli> & A, const vector<lli> & B, int mod){
	vector<lli> P = convolution<a, 3>(A, B);
	vector<lli> Q = convolution<b, 3>(A, B);
	vector<lli> R = convolution<c, 11>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < SZ(D); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		lli x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 % mod + a*(x2 + (lli)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
    vector<lli> aux(mul);
    for(int i = 0; i<SZ(D); i++) aux[i%mul] = (aux[i%mul] + D[i])%MOD;
	return aux;
}


lli ans = 0;
vector<lli> binPow(VLL A, lli b)
{
    VLL res = {1};
    while(b)
    {
        if(b&1) res = multiply(res, A, MOD);
        b>>=1;
        A = multiply(A, A, MOD);
    }
    return res;
}


int main () {
	fastIO();
    cin>>k>>n>>mul;
    vector<lli> A(mul);
    lli total = 0;
    for(int i = 1; i<=n; i++)
    {
        A[i%mul] += (i%mul==0? 0: 1);
        if(i%mul!=0) total++;
    }
    
    /*
    for(auto x: A) cout << x << " ";
    cout << endl;
    */ 
    vector<lli> ans = binPow(A, k);
    
    total = powerMod(total, k, MOD);
    total = powerMod(total, MOD-2, MOD);
    cout << (ans[0]*total)%MOD << endl;
    

	return 0;
}