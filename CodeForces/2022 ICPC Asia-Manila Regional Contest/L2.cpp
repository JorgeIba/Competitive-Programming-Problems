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
    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}



// Solves for n in the equation a^n = b mod p prime
// n = x*m - y, a^xm = ba^y
lli discreteLogarithm(lli a, lli b, lli p){
    lli m = sqrt(p) + 1;

    unordered_map<lli,lli> rhs;
    lli b_ay = b;
    for(int y = 0; y <= m; y++) {
        rhs[b_ay] = y;
        b_ay = b_ay * a % p;
    }

    lli a_m = powerMod(a, m, p);
    lli a_xm = a_m;
    for(int x = 1; x <= m; x++) {
        if(rhs[a_xm]) {
            return x*m - rhs[a_xm]; // lowest solution
        }
        a_xm = a_xm * a_m % p;
    }

	return -1; //solution not found
}



void main_(){

    lli a, b, s, p, v; cin>>a>>b>>s>>p>>v;

    lli ans = 0;
    if(a == 1) {
        lli left = (v - s + p) % p;
        lli right = powerMod(b, p-2, p);

        ans = left*right % p;
    } else {
        lli inv_a1 = powerMod((a - 1 + p) % p, p-2, p);
        lli right = (s + b * inv_a1 % p) % p;

        if(right == 0) {
            if(v == s) {
                cout << 0 << endl;
            } else {
                cout << "IMPOSSIBLE" << endl;
            }
            return;
        }

        right = powerMod(right, p-2, p);

        lli left = (v + b * inv_a1 % p) % p;
        lli total_right = left * right % p;

        auto n = discreteLogarithm(a, total_right, p);
        ans = n;
    }    

    if(ans == -1){
        cout << "IMPOSSIBLE" << endl;
    } else {
        assert(0 <= ans && ans < p);
        cout << ans << endl;
    }
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

