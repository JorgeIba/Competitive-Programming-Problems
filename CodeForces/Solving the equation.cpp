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
 
int k, n;

const lli MOD = 998244353;

template<int p=998244353, int g=3, typename T>
vector<T> multiply(vector<T> A, vector<T> B){ //O(n logn) it uses NTT
    if(B.empty()) return A;
	int sz = SZ(A) + SZ(B) - 1;
	int size = nearestPowerTwo(sz);
    
	A.resize(size), B.resize(size);
	ntt<p, g>(A, false); ntt<p, g>(B, false);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, true);

	A.resize( n+1 );
	return A;
}

//O(n log n)
lli p = MOD;
template<typename T> //Returns 1 / F, with d coeffs
vector<T> invertPolynomio(vector<T> F, int d) 
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

auto binPowP(VLL P, int b)
{
	VLL ans = {1};
	while(b)
	{
		if(b&1) ans = multiply(ans, P);
		b>>=1;
		P = multiply(P, P);
	}
	return ans;
}

const int maxK = 1e5+10;
vector<lli> fact(maxK, 1), inv(maxK, 1), invfact(maxK, 1);

void prec()
{
	for(lli i = 2; i < maxK; ++i)
	{
		fact[i] = i * fact[i-1] % MOD;
		inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
		invfact[i] = (lli)inv[i] * invfact[i-1] % MOD;
	}
}

lli nCr(lli n, lli r)
{
	return ((fact[n] * invfact[n-r])%MOD * invfact[r])%MOD;
}

int main () {
	//fastIO();
	prec();
    cin>>k;
    vector<int> a(k);
    for(auto &x: a) cin>>x;
    cin>>n;
    vector<int> fr(11);
    for(auto &x: a) fr[x]++;
	VLL ans = {1};
    for(int i = 1; i<=10; i++)
    {
		VLL aux(i*fr[i]+1);
		for(int j = 0; j<=fr[i]; j++)
		{
			aux[i*j] = nCr(fr[i], j) *  (j&1?-1:1);
		}
		ans = multiply(ans, aux);
    }
	ans = invertPolynomio(ans, n);
	for(int i = 0; i<=n; i++) 
		cout << ans[i] << " ";
	cout << endl;



	return 0;
}