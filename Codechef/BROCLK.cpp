#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int MOD = 1e9+7;
const int mod = MOD;


lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


lli sqr;
struct Ext{
    lli a, b;

    Ext(): a(0), b(0) {}
    Ext(lli a, lli b): a(a), b(b) {}

    Ext operator*(const Ext &A) const {
        lli new_a = (a * A.a % mod + sqr * b % mod * A.b % mod) % mod;
        lli new_b = (a * A.b % mod + b * A.a % mod) % mod;

        return {new_a, new_b};
    }

    Ext operator+(const Ext &A) const{ return {(a + A.a) % mod, (b + A.b) % mod}; }
    Ext operator-(const Ext &A) const{ return {(a - A.a + mod) % mod, (b - A.b + mod) % mod};}
    Ext operator*(const lli k) const{ return {a * k % mod, b * k % mod}; }
    bool operator==(const Ext &A) const{ return a == A.a && b == A.b; }
    bool operator!=(const Ext &A) const{ return !(*this == A); }

    Ext power(lli k) const {
        Ext res = Ext(1, 0);
        for(auto A = *this; k; k >>= 1, A = A * A){
            if(k&1) res = res * A;
        } 
        return res;
    }

    Ext conj() const {
        return {a, mod - b};
    }

    Ext inv() const {
        lli den = a*a%mod - sqr*b%mod*b%mod;
        if(den < 0) den += mod;
        return conj() * powerMod(den, mod-2, mod);
    }
};


struct Complex{
    Ext a, b;

    Complex() {}
    Complex(Ext a, Ext b): a(a), b(b) {}

    Complex operator+(const Complex &A) const { return {a + A.a, b + A.b}; }
    Complex operator-(const Complex &A) const { return {a - A.a, b - A.b}; }
    Complex operator*(const Ext &k) const { return {a*k, b*k}; }

    Complex operator*(const Complex &A) const {
        Ext new_a = a*A.a - b*A.b;
        Ext new_b = b*A.a + a*A.b;

        return {new_a, new_b};
    }

    Complex power(lli k) const{
        Complex res(Ext(1, 0), Ext(0,0));
        auto A = *this;
        while(k){
            if(k&1) res = res * A;
            k >>= 1;
            A = A * A;
        }
        return res;
    }
};




void main_(){
    lli l, d, t; cin>>l>>d>>t;

    sqr = (l*l - d*d + MOD) % MOD;

    lli inv_l = powerMod(l, MOD-2, MOD);

    Complex coeff = Complex(Ext(0,0), Ext(powerMod(inv_l, t-1, MOD), 0));
    Complex rho =   Complex(Ext(d, 0), Ext(0, MOD - 1));

    Complex Ans = coeff * rho.power(t);

    cout << Ans.b.a << endl;
}


int main () {
	// fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

