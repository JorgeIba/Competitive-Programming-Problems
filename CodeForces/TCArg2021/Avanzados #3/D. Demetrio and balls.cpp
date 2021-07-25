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


template<typename T>
struct Poly{
    vector<T> P;
    const int p = 998244353 ; //!! change for MOD

    Poly(){}
    Poly(int n, int value = 0): P(n, value) {}
    Poly(vector<T> A) {P = A;}

    void normalize(){ while(!P.empty() && !P.back()) P.pop_back();} // get rid of leading zeroes

    inline int size() const{return P.size();}
    inline void resize(int n) {P.resize(n);}

    T &operator[] (int i){ return P[i]; }
    const T &operator[] (int i) const{ return P[i]; } // To get access without dot

    void operator=(vector<T> A){this->P=A;}
    void operator=(Poly<T> A){this->P=A.P;}

    T add(T a, T b)
    {
		if(p == 1) return a+b;
	    return a+b<p? a+b: a+b-p;
    }

    T sub(T a, T b)
	{
		if(p == 1) return a-b;
		return a-b<0?a-b+p:a-b;
	}

    T mul(T a, T b)
    {
		if(p == 1) return a*b;
        return (a*b)%p;
    }

	T inv(T n)
    {
        if(p == 1) return 1 / n;
        return powerMod(n, p-2, p); //!!MOD
    }


    Poly operator+(const Poly<T> &A) { 
        Poly<T> ans(max(SZ(P), SZ(A.P)));
        for(int i = 0; i < SZ(ans); i++){
            T a = 0, b = 0;
            if(i<SZ(P)) a = P[i];
            if(i<SZ(A)) b = A[i];
            ans[i] = add(a,b);
        }
        ans.normalize();
        return ans;
    }

    Poly operator-(const Poly<T> &A) { 
        Poly<T> ans(max(SZ(P), SZ(A.P)));
        for(int i = 0; i < SZ(ans); i++){
            T a = 0, b = 0;
            if(i<SZ(P)) a = P[i];
            if(i<SZ(A)) b = A[i];
            ans[i] = sub(a,b);
        }
        ans.normalize();
        return ans;
    }

    Poly operator*(int k) { 
        Poly<T> ans( SZ(P) );
        for(int i = 0; i < SZ(ans); i++){
            ans[i] = mul(P[i], k);
        }
        return ans;
    }

    Poly operator*(const Poly<T> &A) { 
        return multiply(A.P, P);
    }

    vector<Poly<T>> STM;
    Poly multiMultiply(const vector<Poly<T>> &Polys)
    {
        int n = (int)Polys.size();
        STM.resize(2*n);
        for(int i = n; i<2*n; i++) STM[i] = Polys[i-n];
        for(int i = n-1; i; i--) STM[i] = STM[i<<1] * STM[i<<1 | 1];
        return STM[1];
    }

};
template<typename T>
ostream& operator<<(ostream &so, const Poly<T> &A)
{
    for(auto x: A.P) so<<x<<" ";
    return so;
}




int main () {
	fastIO();
    lli n; cin>>n;

    vector<Poly<lli>> polys(n);
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        polys[i] = Poly<lli>(x+1,1);
    }

    
    Poly<lli> ANS = Poly<lli>(1).multiMultiply(polys);

    lli q; cin>>q;
    while(q--)
    {
        lli t; cin>>t;
        if(t >= SZ(ANS)) cout << 0 << endl;
        else cout << ANS[t] << endl;
    }
	
	return 0;
}

