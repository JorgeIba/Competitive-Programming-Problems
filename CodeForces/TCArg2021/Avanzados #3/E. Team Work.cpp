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


int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
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

template<int p, int g>
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

template<int p, int g>
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


//convolution with arbitrary modulo using CRT
//slower but with no precision errors
const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = powerMod(a, b-2, b), a_c = powerMod(a, c-2, c), b_c = powerMod(b, c-2, c);
vector<lli> multiply(const vector<lli> & A, const vector<lli> & B, int mod = 1e9+7){
	vector<lli> P = convolution<a, 3>(A, B);
	vector<lli> Q = convolution<b, 3>(A, B);
	vector<lli> R = convolution<c, 11>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < SZ(D); ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		int x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 % mod + a*(x2 + (lli)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}


template<typename T>
struct Poly{
    vector<T> P;
    const int p = 1e9+7; //!! change for MOD

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
     
    Poly invert(int d = -1) //Returns 1 / F, with d coeffs
    {
        if(d==-1) d = SZ(P);
        Poly<T> R_n = vector<T>{ inv(P[0]) }; //equivalent to: 1 / F[0]
        while(SZ(R_n) <= d)
        {
            int j = 2*SZ(R_n);
            Poly<T> FF = P; FF.resize(j);
            Poly<T> RnF = R_n*FF;
            for(auto &x: RnF.P) x = sub(0,x);
            RnF[0] = add(RnF[0], 2);
            R_n = R_n * RnF;
            R_n.resize(j);
        }
        R_n.resize(d+1);
        return R_n;
    }

    Poly operator/(Poly<T> B) { //Returns Q -> A = Q*B + R
        Poly<T> A = *this;
        int n = SZ(A), m = SZ(B);
        if(n < m) return vector<T>{0};
        reverse(all(A.P)); reverse(all(B.P));
        A.resize(n-m+1); B.resize(n-m+1);
        Poly<T> Q =  A * B.invert();
        Q.resize(n-m+1);
        reverse(all(Q.P));
        return Q;
    }

    Poly operator%(const Poly<T> &B) { //Return R = A - Q*B
        Poly<T> A = *this;
        int n = SZ(A),  m = SZ(B);
        if(n >= m){
            Poly<T> R = (A/B)*B;
            A.resize(m-1);
            for(int i = 0; i<m-1; i++){
                A[i] = sub(A[i], R[i]);
            }
        }
        return A;
    }


    vector< Poly > STE; //Segment Tree - Evaluate
    void buildSTE(vector<T>&x){ //(x-x_0)(x-x_1)(x-x_2)...(x-x_n)
        int n = SZ(x);
        STE.resize(2*n);
        for(int i = n; i<2*n; i++) STE[i] = vector<T>{sub(0, x[i-n]), 1}; //Ojo: MOD
        for(int i = n-1; i; i--) STE[i] = STE[i<<1] * STE[i<<1 | 1];
    }

    vector<T> multiEvaluate(vector<T> &x){
        buildSTE(x);
        int m = SZ(x);
        vector< Poly<T> > ans(2*m);
        ans[1] = (*this) % STE[1];
        for(int i = 2; i<2*m; i++) ans[i] = ans[i>>1] % STE[i];
        vector<T> evals(m);
        for(int i = m; i<2*m; i++) evals[i-m] = ans[i][0];
        return evals;
    }

	Poly derivate(){
		int n = SZ(P);
		Poly<T> ans(n-1);
		for(int i = 1; i<n; i++)
			ans[i-1] = mul(P[i],i);
		return ans;
	}
    

	Poly interpolate(vector<T> &x, vector<T> &y)
	{
		buildSTE(x);
		int n = SZ(x);
		Poly<T> pp = STE[1].derivate();
		vector<T> d = pp.multiEvaluate(x);
		vector< Poly<T> > inTree(2*n);
		STE = pp.STE;
		for(int i = n; i<2*n; i++)
            inTree[i] = vector<T>{ mul(y[i-n], inv(d[i-n])) }; //y_i / d_i
		for(int i = n-1; i; i--)
			inTree[i] =  inTree[i<<1] * STE[i<<1|1] + inTree[i<<1|1] * STE[i<<1];
		return inTree[1];
	}



    T eval(T a){
        T sum = 0, x = 1;
        for(int i = 0; i<SZ(P); i++){
            sum = add(sum, mul(x, P[i]));
            x = mul(x, a);
        }
        return sum;
    }
};

template<typename T>
ostream& operator<<(ostream &so, const Poly<T> &A)
{
    for(auto x: A.P) so<<x<<" ";
    return so;
}

//13
const lli maxN = 1e6+100;
const lli MOD = 1e9+7; // Initialize
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r)
{
    if( r < 0 || n < r) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a*a % MOD;
    }
    return res;
}

lli f(lli n, lli k)
{
    lli sum = 0;
    for(lli i = 1; i<=n; i++)
    {
        sum += binPow(i, k) * nCr(n, i) % MOD;
        if(sum >= MOD) sum -= MOD;
    }
    return sum * binPow( binPow(2, n), MOD-2 ) % MOD;
}


int main () {
	fastIO();
    prec();
	lli n, k; cin>>n>>k;
    lli maxL = k+10;
    vector<lli> x(maxL), y(maxL);
 
    for(int i = 1; i<maxL; i++)
    {
        x[i] = i;
        y[i] = f(i, k);
    }

    auto ANS = Poly<lli>(1).interpolate(x, y);
    //cout << ANS << endl;
    cout << ANS.eval(n) * binPow(2, n) % MOD << endl;

	return 0;
}

