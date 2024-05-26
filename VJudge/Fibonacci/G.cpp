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

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

int sqr = 5;
const int mod = MOD;
struct Ext{
    lli a, b;

    Ext(): a(0), b(0) {}
    Ext(lli aa, lli bb=0): a(aa), b(bb) {}

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
    Ext operator*(const lli k) const{
        return {1LL*a * k % mod, 1LL*b * k % mod}; 
    }
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


const int MAXN = 2e3+100;
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec()
{
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = 1LL*i*fact[i-1] %MOD;
        inv[i] = MOD - 1LL*(MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = 1LL*inv[i]*invFact[i-1]%MOD;
	}
}

int nCr(int n, int r) {
    if(n < 0 || r > n || r < 0) return 0;
    return 1LL*fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


const lli inv_2 = (MOD+1)/2;

lli sqrtMod(lli a, lli p) {
    if(p == 2) return a;
    if(a % p == 0) return 0;
    if( powerMod(a, (p-1)/2, p) == p-1 ) return -1;
    if(p % 4 == 3) return powerMod(a, (p+1)/4, p);

    lli S = 0, q = p-1;
    while(~q & 1) q>>=1, S++;

    lli n = 2;
    while(powerMod(n, (p-1)/2, p) != p-1) n++;

    lli M = S;
    lli c = powerMod(n, q, p);
    lli t = powerMod(a, q, p);
    lli R = powerMod(a, (q+1)/2, p);

    while(true) {
        if(t == 1) return R;

        lli aux_t = t;
        int m = 1;
        for(; m < M; m++) {
            aux_t = aux_t*aux_t % p;
            if(aux_t == 1) break;
        }
        lli b = powerMod(c, 1LL<<(M-m-1), p);
        M = m;
        c = b*b % p;
        t = t*c % p;
        R = R*b % p;
    }
}


lli sqrtt(lli x){

    lli sr = sqrt(x); sr-=10;
    forn(_, 20) {
        if(sr > 0 && sr*sr == x){
            return sr;
        }
        sr++;
    }

    return -1;
}

inline lli _main(lli a, lli b, lli x, lli y, lli n, lli k){    
    if(a == 0 && b == 0){
        if(k == 0){
            return (n+1)%MOD;
        }

        x = powerMod(x, k, MOD);
        y = powerMod(y, k, MOD);

        if(n == 0) return x;
        return (x+y) % MOD;
    }

    sqr = a*a + 4*b;
    

    Ext r_1(a*inv_2 % MOD, inv_2);
    Ext r_2(a*inv_2 % MOD, MOD-inv_2);

    lli sqrttt = sqrtt(sqr);
    lli sqr_mod = sqrtMod(sqr, MOD);
    if(sqrttt != -1){
        r_1.a = (a + sqrttt) * inv_2 % MOD;
        r_1.b = 0;

        r_2.a = (a - sqrttt + MOD) * inv_2 % MOD;
        r_2.b = 0;
    } else if(sqr_mod != -1){
        r_1.a = (a + sqr_mod) * inv_2 % MOD;
        r_1.b = 0;

        r_2.a = (a - sqr_mod + MOD) * inv_2 % MOD;
        r_2.b = 0;
    }

    Ext yy = Ext(y), xx = Ext(x);

    Ext a_2 = (yy - xx*r_1) * (r_2 - r_1).inv();
    Ext a_1 = xx - a_2;

    Ext ans(0,0);
    for(int j = 0; j <= k; j++){
        Ext x = r_1.power(j) * r_2.power(k-j);

        Ext num = x.power(n+1) - Ext(1);
        Ext den = x - Ext(1);

        Ext sum = (x == Ext(1) ? Ext((n+1)%MOD) : num * den.inv());

    
        Ext ans_j = Ext(nCr(k,j)) * a_1.power(j) * a_2.power(k-j) * sum;    
        ans = ans + ans_j;
    }


    return ans.a;
}



int main () {
	// fastIO();

    prec();

    int t; cin>>t;

    forr(i, 1, t){
        lli a, b, x, y, n, k; cin>>a>>b>>x>>y>>n>>k;

        auto ans = _main(a, b, x, y, n, k);
        cout << ans << endl;
    }

	return 0;
}

