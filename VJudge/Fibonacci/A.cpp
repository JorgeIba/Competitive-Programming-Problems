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

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

template<int sqr=5,int mod=1'000'000'000+7>
struct Ext{
    lli a, b;

    Ext(): a(0), b(0) {}
    Ext(lli a, lli b=0): a(a), b(b) {}

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


const int MOD = 1e9+7;
int main () {
	//fastIO();
    const int inv_2 = (MOD+1)/2;

    Ext phi(inv_2, inv_2), rho = phi.conj();

    lli n; cin>>n;

    auto ans = (phi.power(n) - rho.power(n)) * Ext(0, 1).inv();

    cout << ans.a << endl;


	return 0;
}

