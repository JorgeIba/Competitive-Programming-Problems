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


lli powerMod(lli a, lli b, lli mod){
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
const lli MAXN = 250;
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec()
{
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = i*fact[i-1] % MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

typedef vector<lli> Poly;

Poly operator*(const Poly &A, const Poly &B) {
    Poly C(SZ(A) + SZ(B) - 1);

    forn(i, SZ(A)) {
        forn(j, SZ(B)) {
            C[i+j] += A[i] * B[j] % MOD;
            if(C[i+j] >= MOD) C[i+j] -= MOD;
        }
    }
    return C;
}

const lli inv_2 = (MOD+1)/2;

Poly div_and_conq (int l, int r){
    if(l == r) return {MOD-l, 1};

    int mid = (l+r)/2;

    auto left = div_and_conq(l, mid);
    auto right = div_and_conq(mid+1, r);

    return left * right;
};

int main () {
	fastIO();

    prec();

    lli k, l, r; cin>>k>>l>>r;

    auto C = div_and_conq(0, k-1);
    for(auto &c: C) c = c * invFact[k] % MOD;
    

    auto G = [&](lli n, lli k) {
        Ext ans;
        Ext x(inv_2, inv_2);
        Ext y(inv_2, MOD - inv_2);

        for(int j = 0; j <= k; j++) {
            Ext sum;
            for(int l = 0; l <= j; l++){
                Ext r = x.power(l) * y.power(j-l);

                Ext left = Ext(nCr(j, l)) * x.power(2*l) * y.power(2*(j-l));

                Ext num = r - r.power(n+1);
                Ext den = Ext(1) - r;

                Ext right = (r != Ext(1) ? num * den.inv() : Ext(n%MOD));

                if((j-l) & 1) {
                    sum = sum - left*right;
                } else {
                    sum = sum + left*right;
                }
            }
            ans = ans + sum * Ext(C[j]) * Ext(0, 1).inv().power(j);
        }
        return ans;
    };


    lli left = l == 1 ? 0 : G(l-1, k).a;
    lli right = G(r, k).a;

    cout << (right - left + MOD) % MOD << endl;


	return 0;
}

