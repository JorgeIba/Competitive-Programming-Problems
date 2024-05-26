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

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

struct EXT{
    lli a, b;

    EXT(): a(0), b(0) {}
    EXT(lli a, lli b=0): a(a), b(b) {}

    EXT operator*(const EXT &A) const {
        lli new_a = a * A.a % MOD +  5 * b * A.b % MOD;
        if(new_a >= MOD) new_a -= MOD;

        lli new_b = a * A.b % MOD + b * A.a % MOD;
        if(new_b >= MOD) new_b -= MOD;

        return {new_a, new_b};
    }

    EXT operator+(const EXT &A) const{
        return {(a + A.a) % MOD, (b + A.b) % MOD};
    }

    EXT operator-(const EXT &A) const{
        return {(a - A.a + MOD) % MOD, (b - A.b + MOD) % MOD};
    }

    EXT operator*(const lli k) const{
        lli new_a = a * k % MOD;
        if(new_a < 0) new_a += MOD;

        lli new_b = b * k % MOD;
        if(new_b < 0) new_b += MOD;

        return {new_a, new_b};
    }

    bool operator==(const EXT &A) const {
        return a == A.a && b == A.b;
    }

    bool operator!=(const EXT &A) const {
        return !(*this == A);
    }

    EXT power(lli k) const {
        EXT res = EXT(1, 0);
        auto A = EXT(a, b);
        while(k){
            if(k&1) res = res * A;
            k >>= 1;
            A = A * A;
        } 
        return res;
    }

    EXT conj() const {
        return {a, MOD - b};
    }

    EXT inv() const {
        lli den = a*a%MOD - 5*b*b%MOD;
        den %= MOD;
        if(den < 0) den += MOD;
        return conj() * powerMod(den, MOD-2);
    }
};


const lli MAXN = 2e5;
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec()
{
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

const lli inv_2 = (MOD+1)/2;

lli check(lli n, lli k){
    vector<lli> fibo(n+1);
    fibo[1] = fibo[2] = 1;

    for(int i = 3; i <= n; i++){
        fibo[i] = (fibo[i-1] + fibo[i-2]) % MOD;
    }

    lli sum = 0;
    for(int i = 1; i <= n; i++){
        (sum += powerMod(fibo[i], k)) %= MOD;
    }

    return sum;
};

int main () {
	//fastIO();

    prec();

    lli n, k; cin>>n>>k;


    EXT ANS(0,0);
    EXT X(inv_2, inv_2);
    EXT Y(inv_2, MOD-inv_2);
    
    for(int j = 0; j <= k; j++){
        EXT R = X.power(j) * Y.power(k-j);

        EXT NUM = R - R.power(n+1);
        EXT DEN = EXT(1) - R;

        EXT B = (R != EXT(1) ? NUM * DEN.inv() : EXT(n%MOD));

        EXT ANS_J = EXT( nCr(k,j) ) * B;

        if((k-j) & 1)
            ANS = ANS - ANS_J;
        else 
            ANS = ANS + ANS_J;
    }


    ANS = ANS * EXT(0, 1).inv().power(k);

    cout << ANS.a << endl;

	return 0;
}

