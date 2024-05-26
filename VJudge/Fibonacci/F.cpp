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

const int MAXN = 2e5+100;
const int MOD = 1e9+7; 

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

const int sqr = 5;
const int mod = MOD;
struct Ext{
    int a, b;

    Ext(): a(0), b(0) {}
    Ext(lli a, lli b=0): a(a), b(b) {}

    Ext operator*(const Ext &A) const {
        int new_a = (1LL*a * A.a % mod + 1LL*sqr * b % mod * A.b % mod) % mod;
        int new_b = (1LL*a * A.b % mod + 1LL*b * A.a % mod) % mod;

        return {new_a, new_b};
    }

    Ext operator+(const Ext &A) const{ 
        int new_a = a + A.a;
        if(new_a >= mod) new_a -= mod;

        int new_b = b + A.b;
        if(new_b >= mod) new_b -= mod;
        return {new_a, new_b};
    }
    Ext operator-(const Ext &A) const{ 
        int new_a = a - A.a;
        if(new_a < 0) new_a += mod;

        int new_b = b - A.b;
        if(new_b < 0) new_b += mod;
        return {new_a, new_b};
    }
    Ext operator*(const lli k) const{ return {1LL*a * k % mod, 1LL*b * k % mod}; }
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
        int den = 1LL*a*a%mod - 1LL*sqr*b%mod*b%mod;
        if(den < 0) den += mod;
        return conj() * powerMod(den, mod-2, mod);
    }
};



vector<int> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec()
{
    for(int i = 2; i <= MAXN; ++i){
        fact[i] = 1LL*i*fact[i-1] %MOD;
        inv[i] = MOD - 1LL*(MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = 1LL*inv[i]*invFact[i-1]%MOD;
	}
}

int nCr(int n, int r) {
    if(n < 0 || r > n || r < 0) return 0;
    return 1LL*fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


typedef Ext Extt;

const int inv_2 = (MOD+1)/2;
const Extt phi(inv_2, inv_2);
const Extt rho(inv_2, MOD-inv_2);
const Extt sqr5(0, 1);
const Extt inv_5 = sqr5.inv();

inline int _main(lli N, lli C, int K){
    
    Extt ans(0,0);

    Extt phi_c = phi.power(C);
    Extt rho_c = rho.power(C);

    for(int j = 0; j <= K; j++){
        Extt r = phi_c.power(j) * rho_c.power(K-j);
        Extt num = r.power(N+1) - r;
        Extt den = r - Extt(1);

        Extt s = (r != Extt(1) ? num * den.inv() : Extt(N%MOD));

        Extt ans_j = Extt(nCr(K, j)) * s;

        if((K-j) & 1){
            ans = ans - ans_j;
        } else {
            ans = ans + ans_j;
        }
    }

    ans = ans * inv_5.power(K);

    return ans.a;
}



int main () {
	fastIO();

    prec();

    int t; cin>>t;

    forr(i, 1, t){
        lli N, C;
        int K; cin>>N>>C>>K;

        auto ans = _main(N, C, K);
        cout << "Case " << i << ": " << ans << endl;
    }
    

	return 0;
}

