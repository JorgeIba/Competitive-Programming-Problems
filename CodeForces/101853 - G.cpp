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


lli powerMod(lli a, lli b, lli m) {
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return res;
}

lli discreteLogarithm(lli a, lli b, lli mod) {
    if(a == 0) {
        if(b != 0) return -1;
        return 1;
    }

    
    lli g, offset = 0, k = 1;
    while((g = gcd(a, mod)) > 1){

        // k*a^(x-add) = k -> (n-offset) = 0
        if(b == k) return offset;

        if(b % g != 0) return -1;

        b /= g;
        mod /= g;
        offset++;

        k = k * (a / g) % mod;
    }

    a %= mod;
    b %= mod;

    // Here we have k * a^(n-offset) = b mod m,
    // gcd(a,m) = 1
    // Lets solve for k*a^x = b mod m

    lli m = sqrt(mod) + 1;

    unordered_map<lli,lli> rhs;
    lli b_ay = b;
    for(int y = 0; y <= m; y++) {
        rhs[b_ay] = y;
        b_ay = b_ay * a % mod;
    }

    lli a_m = powerMod(a, m, mod);
    lli k_axm = k * a_m % mod;
    for(int x = 1; x <= m; x++) {
        if(rhs.count(k_axm)) {
            return offset + (m*x - rhs[k_axm]);
        }
        k_axm = k_axm * a_m % mod;
    }

    return -1;
}



int main () {
	fastIO();
	
    int t; cin>>t;
    while(t--) {
        lli x, y, m; cin>>x>>y>>m;

        auto ans = discreteLogarithm(x, y, m);

        cout << ans << endl;
    }


	return 0;
}

