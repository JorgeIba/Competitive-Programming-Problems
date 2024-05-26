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

const lli MOD = 1e9+9;

#define i128 __int128

lli powerMod(lli a, lli b, lli mod){ 
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


// lli sqrtMod(lli a, lli p) {
//     if(p == 2) return a;
//     if(a % p == 0) return 0;
//     if( powerMod(a, (p-1)/2, p) == p-1 ) return -1;
//     if(p % 4 == 3) return powerMod(a, (p+1)/4, p);

//     lli S = 0, q = p-1;
//     while(~q & 1) q>>=1, S++;

//     lli n = 2;
//     while(powerMod(n, (p-1)/2, p) != p-1) n++;

//     lli M = S;
//     lli c = powerMod(n, q, p);
//     lli t = powerMod(a, q, p);
//     lli R = powerMod(a, (q+1)/2, p);

//     while(true) {
//         if(t == 1) return R;

//         lli aux_t = t;
//         int m = 1;
//         for(; m < M; m++) {
//             aux_t = aux_t*aux_t % p;
//             if(aux_t == 1) break;
//         }
//         lli b = powerMod(c, 1LL<<(M-m-1), p);
//         // for(int i = 0; i < M-m-1; i++) b = b*b % p;
//         M = m;
//         c = b*b % p;
//         t = t*c % p;
//         R = R*b % p;
//     }
// }



int main () {
	//fastIO();

    // lli sqrt5 = sqrtMod(5, MOD);
    // lli inv_2 = powerMod(2, MOD-2, MOD);
    // lli inv_sqrt5 = powerMod(sqrt5, MOD-2, MOD);

    const lli n = 1e18;

    lli sqrt5 = 616991993;
    lli inv_2 = (MOD + 1) / 2;
    lli inv_sqrt5 = 723398404;

    lli phi      = (1 + sqrt5) * inv_2 % MOD;
    lli conj_phi = (1 - sqrt5 + MOD) * inv_2 % MOD;

    
    auto inv = [&](lli n) {
        return powerMod(n, MOD-2, MOD);
    };

    auto G = [&](lli n, lli var_phi){
        lli r = powerMod(var_phi * inv_2 % MOD, n, MOD) % MOD;
        lli inv_phi = inv(var_phi);

        return r * inv(1-r+MOD) % MOD * inv_phi % MOD;
    };


    lli ans = inv_sqrt5 % MOD * (G(n, phi) - G(n, conj_phi) + MOD) % MOD;
    cout << ans << endl;



	return 0;
}

