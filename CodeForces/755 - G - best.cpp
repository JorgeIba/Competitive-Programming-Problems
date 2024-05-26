#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;
int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

lli powerMod(lli a, lli b, lli mod){
	lli res = 1;
    a %= mod;
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

const int MOD = 998244353;

template<typename T>
struct Poly{
    vector<T> P;
    const int p = MOD; //!! change for MOD

    Poly(){}
    Poly(int n, int value = 0): P(n, value) {}
    Poly(vector<T> A) {P = A;}

    void normalize(){ while(P.size() > 1 && !P.back()) P.pop_back();} // get rid of leading zeroes

    inline int size() const{return P.size();}
    inline void resize(int n) {P.resize(n);}

    T &operator[] (int i){ return P[i]; }
    const T &operator[] (int i) const{ return P[i]; } // To get access without dot

    void operator=(vector<T> A){this->P=A;}
    void operator=(Poly<T> A){this->P=A.P;}

    T add(T a, T b){
        a %= p, b %= p;
		if(p == 1) return a+b;
	    return a+b<p? a+b: a+b-p;
    }

    T sub(T a, T b){
        a %= p, b %= p;
		if(p == 1) return a-b;
		return a-b<0?a-b+p:a-b;
	}

    T mul(T a, T b){
        a %= p, b %= p;
		if(p == 1) return a*b;
        return (a*b)%p;
    }

	T inv(T n){
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

    Poly operator*(lli k) { 
        Poly<T> ans( SZ(P) );
        for(int i = 0; i < SZ(ans); i++){
            ans[i] = mul(P[i], k);
        }
        normalize();
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

    Poly shift_left(int n) {
        Poly A;
        A.P.insert(A.P.begin(), P.begin() + n, P.end());
        return A;
    }

    Poly shift_right(int n) {
        Poly A(n);
        A.P.insert(A.P.begin()+n, P.begin(), P.end());
        return A;
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


	Poly derivate(){
		int n = SZ(P);
		Poly<T> ans(n-1);
		for(int i = 1; i<n; i++)
			ans[i-1] = mul(P[i],i);
		return ans;
	}
    
    Poly integrate(){
        Poly<T> A(SZ(P) + 1);
        for(int i = 1; i<=SZ(P); i++)
            A[i] = mul(P[i-1], inv(i));
        return A;
    }

    Poly logn(){
        assert(P[0] == 1);
        int n = SZ(P);
        Poly<T> A = (((*this).derivate()) * ((*this).invert())).integrate();
        A.resize(n);
        return A;
    }

    Poly exp(int d = -1){ //E(x) = E(x)(1-ln(E(x))+A(x))
        if(d == -1) d = SZ(P);
        assert(P[0] == 0);
        Poly<T> E(1,1);
        while(SZ(E) < d){
            int c = 2*SZ(E);
            E.resize(c);
            Poly<T> S = E.logn();
            S = (*this)-S;
            S[0] = 1;
            E = E * S;
            E.resize(c);
        }
        E.resize(d);
        return E;
    }


    Poly pow(lli n, int coeffs = -1) {
        if( coeffs < 0 ) coeffs = size();

        if(n == 0){
            Poly ANS(1,1);
            ANS.resize(coeffs);
            return ANS;
        }

        int t = 0;
        while(t < size() && !P[t]) t++;

        if(t == size() || t > coeffs / n) return Poly(coeffs, 0);

        lli coeff_k = powerMod(P[t], n, p);
        lli inv_coeff = powerMod(P[t], p-2, p);

        Poly B = shift_left(t) * inv_coeff;
        Poly B_ln = B.logn() * n;

        Poly B_k = (B_ln).exp(coeffs - n*t);

        Poly P_n = B_k.shift_right(n*t) * coeff_k;

        return P_n;
    }

    Poly sqrt(int d = -1){
        if(d == -1) d = SZ(P);
        T r0 = 1; //! r0^2 == P[0] mod p
        T inv2 = inv(2);
        Poly<T> R(1, r0); 
        while(SZ(R) <= d)
        {
            int c = 2*SZ(R);
            R.resize(c);
            Poly<T> F = P;
            F.resize( min(c, SZ(P)) );
            F = F * (R.invert());
            for(int i = 0; i<c; i++)
                R[i] = (R[i] + F[i])*inv2 % p;
        }
        
        return R;
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

    int n, m; cin>>n>>m;

    Poly<lli> discr = vector<lli>{1, 6, 1};

    auto sqrt_sol = discr.sqrt(m);
    Poly<lli> b = vector<lli>{1, 1};


    auto r_1 = (b + sqrt_sol);
    for(auto &x: r_1.P)
        x = x*powerMod(2, MOD-2, MOD) % MOD;


    auto r_2 = (b - sqrt_sol);
    for(auto &x: r_2.P)
        x = x*powerMod(2, MOD-2, MOD) % MOD;

    Poly<lli> P_0 = vector<lli>{1};
    Poly<lli> P_1 = vector<lli>{1, 1};


    auto A = (P_1 - r_2) * ((r_1 - r_2).invert(m));
    A.resize(m+1);
    auto B = Poly<lli>(1,1) - A;
    B.resize(m+1);
    
    auto ANS_1 = A * r_1.pow(n, m+1);
    auto ANS_2 = B * r_2.pow(n, m+1);


    auto ANS = ANS_1 + ANS_2;
    ANS.resize(m+1);
    for(int i = 1; i <= m; i++)
        cout << ANS[i] << " ";
    cout << endl;


	return 0;
}

