#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

int N, M;
const int MOD = 998244353;

typedef vector<int> poly;


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
    A.resize(min(SZ(A), M+1));
	return A;
}


poly operator*(const poly &a, const poly &b) {
    return multiply(a, b);
}

poly operator+(poly a, poly b) {
    if(SZ(a) > SZ(b)) swap(a, b);
    poly c = b;
    for(int i = 0; i < SZ(a); i++){
        c[i] += a[i];
        if(c[i] >= MOD) c[i] -= MOD;
    }
    c.resize(min(SZ(c), M+1));
    return c;
}



template<typename T>
T kthTermLinearRecurrence(const vector<T> & P, const vector<T> & init, lli n){

	int deg = P.size();
	vector<T> ans(deg, poly(1, 0)), R(2*deg);
    // ans[0] = 1
	ans[0] = poly(1, 1);
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), T(1, 0));
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] = (R[i + j + d] + ans[i] * ans[j]);
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				R[i + j] = (R[i + j] +  R[i + deg] * P[j]);

		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);

	T nValue = T(1, 0);
	for(int i = 0; i < deg; i++)
		nValue = (nValue +  ans[i] * init[i]);
	return nValue;
}
 


int main () {
	fastIO();
	
    cin>>N>>M;

    vector<poly> INIT(2);
    INIT[0] = poly(1, 1);
    INIT[1] = poly(2, 1);


    vector<poly> P(2);
    P[0] = poly{0, 1};
    P[1] = poly(2, 1);


    auto ANS = kthTermLinearRecurrence(P, INIT, N);
    ANS.resize(M+1);
    for(int i = 1; i <= M; i++){
        cout << ANS[i] << " ";
    }
    cout << endl;


	return 0;
}
