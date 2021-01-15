#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,b,n) for (int i = 0; i < n; i++)
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


template<int p = 786433, int g = 10, typename T>
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


const int p = 786433;

template<typename T>
vector<T> invertPolynomio(const vector<T> &F, int d) // R_2n = R_n(2 - R_nF)
{
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


template<typename T> //Q' = A'(1/B') mod x^(n-m+1)
vector<T> division(vector<T> A, vector<T> B) //A = Q*B + R
{
    int n = SZ(A), m = SZ(B);
    if(n < m) return {0};
    reverse(all(A)); reverse(all(B));
    A.resize(n-m+1); B.resize(n-m+1);
    A = multiply(A, invertPolynomio(B, SZ(B)));
    A.resize(n-m+1);
    reverse(all(A));
    return A;
}	

template<typename T> //R = A - Q*B
vector<T> remainder(vector<T> A, const vector<T> &B) 
{
	int n = SZ(A),  m = SZ(B);
	if(n >= m)
	{
		vector<T> R = multiply(division(A, B),B);
		A.resize(m-1);
		for(int i = 0; i<m-1; i++)
		{
			A[i] -= R[i];
			if(A[i] < 0) A[i] += p;
		}
	}
	return A;
}

lli subMod(lli a, lli b)
{
    lli res = (a-b)%p;
    return (res<0? res+p: res);
}

vector< vector<lli> > STE; //Segment Tree - Evaluate
void buildSTE(const vector<lli> &x) //(x-x_0)(x-x_1)(x-x_2)...(x-x_n)
{
	int n = SZ(x);
	STE.resize(2*n);
	for(int i = n; i<2*n; i++) STE[i] = {subMod(0, x[i-n]), 1};
	for(int i = n-1; i; i--) STE[i] = multiply(STE[i<<1], STE[i<<1 | 1]);
}

template<typename T>
vector<T> multiEvaluate(const vector<T> &A, const vector<lli> &x)
{
	buildSTE(x);
	int m = SZ(x);
	vector<vector<T>> ans(2*m);
	ans[1] = remainder(A, STE[1]);
	for(int i = 2; i<2*m; i++) ans[i] = remainder(ans[i>>1], STE[i]);
	vector<T> evals(m);
	for(int i = m; i<2*m; i++) evals[i-m] = ans[i][0];
	return evals;
}


int main () {
	fastIO();
    
    int n; cin>>n; 
    vector<lli> A(n+1);
    for(auto &x: A) cin>>x;
	
    int q; cin>>q;
    vector<lli> x(q);
    for(auto &a: x) cin>>a;

	auto ans = multiEvaluate(A, x);
	for(auto x: ans) 
    {
        assert(x >= 0 && x<p);
        cout << x << "\n";
    }
	return 0;
}