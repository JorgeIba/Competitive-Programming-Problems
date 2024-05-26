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

lli multMod(lli a, lli b, lli mod){
    lli res = 0;
    while(b){
        if(b&1) {
            res = res + a;
            if(res >= mod) res -= mod;
        }
        b >>= 1;
        a = a + a;
        if(a >= mod) a -= mod;
    }
    return res;
}


lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b&1) res = multMod(res, a, mod);
        b >>= 1;
        a = multMod(a, a, mod);
    }
    return res;
}


const lli P = 10, MOD = 212345678987654321LL;
lli PI;

/*
    s_0*p^6 + s_1*p^5 + s_2*p^4 + s_3*p^3 + s_4*p^2 + s_5*p^1 + s_6 mod MOD
*/


const int MAXN = 1e6 + 100;
lli pow_p[MAXN + 10];
lli inv_p[MAXN + 10];

#define i128 __int128

int main () {
	// fastIO();
    PI = powerMod(P, MOD-2, MOD);


    pow_p[0] = 1;
    inv_p[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        pow_p[i] = (i128) pow_p[i-1] * P  % MOD;
        inv_p[i] = (i128) inv_p[i-1] * PI % MOD;
    }


    string s; cin>>s;
    int n = SZ(s);

    vector<lli> suff_hashes(n+1);
    for(int i = n-1; i >= 0; i--) {
        suff_hashes[i] = ((i128) suff_hashes[i+1] + (i128) pow_p[(n-1) - i] * (s[i] - '0') % MOD) % MOD;
    }

    auto get_hash = [&](int l, int r) {
        i128 res = (suff_hashes[l] - suff_hashes[r+1] + MOD) % MOD;
        res = res * inv_p[(n-1) - r] % MOD;
        assert(0 <= res && res < MOD);
        return res;
    };


    for(int i = n-1; i >= 1; i--) {
        int k = (n-1) - i + 1;

        // 1837272167
        // 0123456789
        for(int first_r_: {k-2, k-1, n-2*k, n-2*k-1, n-2*k+1}) {
            int first_l = 0, first_r = first_r_;
            int second_l = first_r + 1, second_r = i-1;
            int third_l = i, third_r = n-1;

            int sz_first  = first_r  - first_l  + 1;
            int sz_second = second_r - second_l + 1;
            int sz_third  = third_r  - third_l  + 1;

            if(sz_first <= 0 || sz_second <= 0 || first_r >= second_l || second_r >= third_l ) continue;
            if(abs(sz_third - max(sz_first, sz_second)) > 2) continue;

            if(s[first_l]  == '0' && sz_first  > 1) continue;
            if(s[second_l] == '0' && sz_second > 1) continue;
            if(s[third_l]  == '0' && sz_third  > 1) continue;

            lli first_hash  = get_hash(first_l,  first_r);
            lli second_hash = get_hash(second_l, second_r);
            lli third_hash  = get_hash(third_l,  third_r);

            if((first_hash + second_hash) % MOD == third_hash) {
                cout << s.substr(0, sz_first) << "+" << s.substr(second_l, sz_second) << "=" << s.substr(third_l, sz_third) << endl;
                return 0;
            }
        }
    }


	return 0;
}

