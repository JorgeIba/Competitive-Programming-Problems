#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

typedef vector<lli> poly;

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


template < class T >
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

const lli MOD = 998244353;



poly DC(int l, int r, const poly &pref_g){
    if(l == r) {
        return {1, pref_g[0]};
    }
	
	int mid = l + (r-l)/2;

	auto first_halg_f = poly(pref_g.begin(), pref_g.begin() + (r-l)/2 + 1);
	poly left = DC(l, mid, first_halg_f);
	
	poly ret = multiply(pref_g, left);
	
	auto range_ret = poly( ret.begin() + (r-l)/2 + 1, ret.begin() + (r-l) + 1);
	poly right = DC(mid+1, r, range_ret);


	return multiply(left, right);
}



int main(){

	lli n, A; cin>>n>>A;

	poly F(n+1);

	lli current = 1;
	F[0] = current;
	for(int i = 1; i <= min((int)A, SZ(F)-1); i++){
		current = current * (A-i+1) % MOD * powerMod(i, MOD-2, MOD) % MOD;
		F[i] = current;
	}

	if(n <= 2){
		cout << F[n] << endl;
		return 0;
	}	

	poly ret = poly(F.begin() + 2, F.begin() + n);

	poly ans_range = DC(2, n-1, ret);
	poly ans = multiply(F, ans_range);

	cout << ans[n] << endl;

	return 0;
}