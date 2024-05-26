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


const int MOD = 999'999'893;

lli powerMod(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

struct Z {
    lli a, b;
    Z(lli a, lli b = 0) : a(a), b(b) {}
    Z operator*(Z A) { lli new_a = (a * A.a % MOD + 2 * b % MOD * A.b % MOD) % MOD; lli new_b = (a * A.b % MOD + b * A.a % MOD) % MOD; return {new_a, new_b};}
    Z operator+(Z A){return {(a + A.a) % MOD, (b + A.b) % MOD};}
    Z operator-(Z A){return {(a - A.a + MOD) % MOD, (b - A.b + MOD) % MOD};}
    Z operator*(lli k){ return {a * k % MOD, b * k % MOD}; }
    bool operator==(Z A){ return a == A.a && b == A.b; }
    bool operator!=(Z A){ return !(*this == A); }
    Z power(lli k) {Z res = Z(1, 0);for (auto A = *this; k; k >>= 1, A = A * A) {if (k & 1)res = res * A;}return res;}
    Z inv(){lli den = a * a % MOD - 2 * b % MOD * b % MOD;if (den < 0)den += MOD;return Z(a, MOD-b) * powerMod(den, MOD - 2);}
};

Z ONE = Z(1, 0);
Z TWO = Z(0, 1);
Z INV_TWO  = TWO.inv();
Z R = Z(2,0) * INV_TWO;

void main_(){
    lli n; cin>>n;

    auto A = R.power(n+1) - R*R;
    auto B = R - ONE;

    auto NUM = Z(4,0)*INV_TWO;
    auto DEN = Z(4,0)*INV_TWO + A*B.inv();
    auto ANS = ONE - NUM * DEN.inv();

    cout << ANS.b << endl;
}

int main () {
	fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

