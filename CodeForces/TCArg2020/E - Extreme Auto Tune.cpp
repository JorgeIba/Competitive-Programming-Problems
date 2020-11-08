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
 
template<int p=998244353, int g=3, typename T>
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
    const int p = 998244353; // change for MOD

    Poly(){}
    Poly(int n): P(n) {}
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
		if(p == -1) return a+b;
	    return a+b<p? a+b: a+b-p;
    }

    T sub(T a, T b)
	{
		if(p == -1) return a-b;
		return a-b<0?a-b+p:a-b;
	}

    T mul(T a, T b)
    {
		if(p==-1) return a*b;
        return (a*b)%p;
    }

	T inv(T n)
    {
        if(p==-1) return 1 / n;
        return powerMod(n, p-2, p);
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
		{
			ans[i-1] = mul(P[i],i);
		}
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
		for(int i = n; i<2*n; i++) inTree[i] = vector<T>{ mul(y[i-n], inv(d[i-n])) }; //y_i / d_i
		for(int i = n-1; i; i--)
		{
			inTree[i] =  inTree[i<<1] * STE[i<<1|1] + inTree[i<<1|1] * STE[i<<1];
		}
		return inTree[1];
	}
};

template<typename T>
ostream& operator<<(ostream &so, const Poly<T> &A)
{
    for(auto x: A.P) so<<x<<" ";
    return so;
}


const int p = 998244353;

int main () {
	fastIO();
	int m, k; cin>>m>>k;
	int tri = k+2;
	vector<lli> points(m);
	for(auto &x: points)
	{
		cin>>x;
		x%=p;
	} 
	vector<lli> x(tri), y(tri);
	lli sum = 0;
	for(int i = 0; i<tri; i++)
	{
		x[i] = i;
		y[i] = (sum+powerMod(i, k, p))%p;
		sum = y[i];
	}

	Poly<lli> poly = Poly<lli>().interpolate(x, y);
	vector<lli> ans = poly.multiEvaluate(points);
	for(auto &x: ans) cout << x <<" ";
	return 0;
}