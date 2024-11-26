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


const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;
lli fact[MAXN], ifact[MAXN];


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

        // You can precalculate this soutside
        fact[0] = ifact[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            fact[i] = fact[i - 1] * i % MOD;
            ifact[i] = powerMod(fact[i], MOD - 2, MOD);
        }

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
	// fastIO();

    int n, k; cin>>n>>k;

    vector<lli> values(k+4);
    lli val = 0;
    for(int i = 0; i < k+4; i++) {
        (val += (powerMod(i, k, MOD))) %= MOD;
        values[i] = val;
    }


    LagrangePoly LP(values);

    lli ans = LP.getVal(n);
    if(k == 0) {
        cout << (ans - 1 + MOD) % MOD << endl;
    } else {
        cout << ans << endl;
    }





	return 0;
}

