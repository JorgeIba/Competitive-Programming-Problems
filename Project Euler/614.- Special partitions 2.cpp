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

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

const lli mod = 1e9 + 7;

template<typename p, typename root, typename root_1, typename root_pw>
void ntt(vector<lli> & X, lli inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(int k = 1; k < n; k <<= 1){
		lli wk = (inv == -1) ? root_1::value : root::value;
		for(int i = k << 1; i < root_pw::value; i <<= 1)
			wk = wk * wk % p::value;
		for(int i = 0; i < n; i += k << 1){
			lli w = 1;
			for(int j = 0; j < k; ++j, w = w * wk % p::value){
				lli u = X[i + j], v = (lli)X[i + j + k] * w % p::value;
				X[i + j] = u + v < p::value ? u + v : u + v - p::value;
				X[i + j + k] = u - v < 0 ? u - v + p::value : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = inverse(n, p::value);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p::value;
	}
}

template<typename p, typename root, typename root_1, typename root_pw>
vector<lli> convolution(vector<lli> A, vector<lli> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, root, root_1, root_pw>(A, 1), ntt<p, root, root_1, root_pw>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = A[i] * B[i] % p::value;
	ntt<p, root, root_1, root_pw>(A, -1);
	A.resize(sz);
	return A;
}

const lli a = 167772161;  //17, 29606852
const lli b = 469762049;  //13, 144542169
const lli c = 1107296257; //309, 996208283
const lli a_b = inverse(a, b);
const lli a_c = inverse(a, c);
const lli b_c = inverse(b, c);
vector<lli> multiply(const vector<lli> & A, const vector<lli> & B){
	vector<lli> P = convolution<integral_constant<lli, a>, integral_constant<lli, 17>, integral_constant<lli, 29606852>, integral_constant<lli, (1 << 25)>>(A, B);
	vector<lli> Q = convolution<integral_constant<lli, b>, integral_constant<lli, 13>, integral_constant<lli, 144542169>, integral_constant<lli, (1 << 25)>>(A, B);
	vector<lli> R = convolution<integral_constant<lli, c>, integral_constant<lli, 309>, integral_constant<lli, 996208283>, integral_constant<lli, (1 << 25)>>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < SZ(D); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		lli x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 + a*(x2 + x3*b % mod) % mod;
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
        return inverse(n, p); //!!MOD
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

};

template<typename T>
ostream& operator<<(ostream &so, const Poly<T> &A)
{
    for(auto x: A.P) so<<x<<" ";
    return so;
}


const lli MOD = 1e9+7;
const lli maxN = 1e7+10;

lli f(lli n)
{
    return n*(2*n+1);
}


int main () {
	//fastIO();

    clock_t start = clock();

    Poly<lli> Px(maxN), Px2(maxN);

    for(lli i = -100000; i<=100000; i++)
    {
        lli idx = f(i);
        if(idx < maxN) Px[idx] = (i&1? MOD-1:1);
        if(2LL*idx < maxN) Px2[2LL*idx] = (i&1? MOD-1:1);
    }

    Px = Px2 * (Px.invert());
    
    lli ans = 0;
    for(int i = 1; i<=1e7; i++)
    {
        ans = (ans + Px[i])%MOD;
    }
    cout << ans << endl;
    

    cout << fixed << setprecision(2) << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

	return 0;
}

/*
lli f(lli n)
{
    return n*(3*n-1) / 2;
}

int main () {
	//fastIO();

    clock_t start = clock();

    Poly<lli> Pi(maxN), P2i(maxN), P4i(maxN), P8i(maxN);
    
    for(lli i = -100000; i<=100000; i++)
    {
        lli idx = f(i);
        if(idx < maxN) Pi[idx] = (i&1? MOD-1: 1);
        if(2LL*idx < maxN) P2i[2LL*idx] = (i&1? MOD-1: 1);
        if(4LL*idx < maxN) P4i[4LL*idx] = (i&1? MOD-1: 1);
        if(8LL*idx < maxN) P8i[8LL*idx] = (i&1? MOD-1: 1);
    }
    
    auto Aux1 = P8i* (P2i * P2i);
    Aux1.resize(maxN);

    auto Aux2 = Pi*P4i*P4i;
    Aux2.resize(maxN);

    auto Aux3 = Aux2.invert(maxN);
    Aux3.resize(maxN);

    auto ANS = Aux1 * Aux3;
    ANS.resize(maxN);


    lli ans = 0;
    for(lli i = 1; i<=(lli)1e7; i++)
    {
        assert(ANS[i] >= 0 && ANS[i] < MOD);
        ans = (ans + ANS[i])%MOD;
        if(i == int(1e4)) cout << ans << endl;
        if(i == int(1e5)) cout << ans << endl;
        if(i == int(1e6)) cout << ans << endl;
    } 
    cout << ans << endl;

    cout << fixed << setprecision(2) << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

	return 0;
}
*/