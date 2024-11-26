#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MAXN = 380;
const lli MOD = 1234567891;
lli fact[MAXN], inv[MAXN], ifact[MAXN];

lli powerMod(lli a, lli b, const lli mod){
    lli res = 1;

    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }

    return res;
}


class LagrangePoly {
  public:
    // f(0), f(1), ..., f(k)
    LagrangePoly(vector<lli> _a) {
        y = _a;
        int n = SZ(y);
        den.resize(n);

        for (int i = 0; i < n; i++) {
            y[i] = (y[i] % MOD + MOD) % MOD;
            den[i] = ifact[n - i - 1] * ifact[i] % MOD;
            if ((n - i - 1) % 2 == 1) {
                den[i] = (MOD - den[i]) % MOD;
            }
        }
    }

    lli getVal(lli x) {
        int n = SZ(y);
        x = (x % MOD + MOD) % MOD;
        if (x < n) {
            return y[(int)x];
        }
        vector<lli> l(n), r(n);
        l[0] = 1;
        for (int i = 1; i < n; i++) {
            l[i] = l[i - 1] * (x - (i - 1) + MOD) % MOD;
        }
        r[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            r[i] = r[i + 1] * (x - (i + 1) + MOD) % MOD;
        }
        lli ans = 0;
        for (int i = 0; i < n; i++) {
            lli coef = l[i] * r[i] % MOD;
            ans = (ans + coef * y[i] % MOD * den[i]) % MOD;
        }
        return ans;
    }

  private:
    vector<lli> y, den;
};

int main () {
	fastIO();

    fact[0] = inv[0] = ifact[0] = 1;
    fact[1] = inv[1] = ifact[1] = 1;
    for (lli i = 2; i < MAXN; ++i) {
        fact[i] = i * fact[i - 1] % MOD;
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        ifact[i] = inv[i] * ifact[i - 1] % MOD;
    }

    vector< LagrangePoly* > polys(325);
    for(int k = 0; k < 325; k++) {
        vector<lli> values2(k+10);
        lli val = 0, val2 = 0;
        for(int i = 1; i < k+10; i++) {
            (val += powerMod(i, k, MOD)) %= MOD;
            (val2 += val);

            if(val2 >= MOD) val2 -= MOD;
            values2[i] = val2;
        }

        polys[k] = new LagrangePoly(values2);
    }



    int t; cin>>t;

    while(t--){
        int n, k; cin>>n>>k;

        cout << polys[k]->getVal(n) << endl;
    }

    





	return 0;
}

