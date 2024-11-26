#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef __int128 lli;
typedef long long ll;
typedef long double ld;



// const int MAXN = 24;
// int dp[1 << MAXN][MAXN];

// int main () {


//     auto f = [&](const auto &f, int mask, int idx, const int n) -> lli {
//         if(__builtin_popcount(mask) == n) {
//             return idx == n-1;
//         }

//         int &ans = dp[mask][idx];
//         if(ans != -1) return ans;

//         ans = 0;
//         for(int i = -3; i <= 3; i++) {
//             if(i == 0) continue;

//             if(!(0 <= (i+idx) && (i+idx) < n)) continue;

//             if(mask & (1 << (i+idx))) continue;
//             ans += f(f, mask | (1 << (i+idx)), i+idx, n);
//         }

//         return ans;
//     };

    
//     forn(i, MAXN) {
//         memset(dp, -1, sizeof(dp));
//         cout << f(f, 1, 0, i) << ", ";
//     }
//     cout << endl;



// 	return 0;
// }


// vector<lli> values = {1, 1, 1, 2, 6, 14, 28, 56, 118, 254, 541, 1140, 2401, 5074, 10738, 22711, 48001, 101447, 214446, 453355, 958395, 2025963, 4282685};
// vector<lli> values = {0, 3, 3, 9, 15, 33};


template<typename T>
T kthTermLinearRecurrence(const vector<T> &P, const vector<T> &init, lli n, const int mod) {
    int deg = SZ(P);
    vector<T> ans(deg), R(2*deg);
    ans[0] = 1;
    
    lli p = 1;
    for(lli v = n; v >>= 1; p <<= 1);
    do {
        int d = (n & p) != 0;
        fill(all(R), T());
        for(int i = 0; i < deg; i++)
            for(int j = 0; j < deg; j++)
                R[i+j+d] = (R[i+j+d] + ans[i] * ans[j] % mod) % mod;
        for(int i = deg - 1; i >= 0; i--)
            for(int j = 0; j < deg; j++)
                R[i+j] = (R[i+j] + R[i + deg] * P[j] % mod) % mod;
        copy(R.begin(), R.begin() + deg, ans.begin());
    }while(p >>= 1);

    T nValue = T();
    for(int i = 0; i < deg; i++) {
        nValue = (nValue + ans[i] * init[i] % mod) % mod;
    }
    return nValue;
}



ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}


lli inverse(lli a, lli n) {
    lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
    while(r1) {
        si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
        ri = r0 % r1, r0 = r1, r1 = ri;
    }
    assert(r0 == 1);
    if(s0 < 0) s0 += n;
    return s0;
}


vector<lli> BerlekampMassey(const vector<lli> &init, const lli mod) {
    vector<lli> cur, ls;
    lli ld=0;
    for(int i = 0, m=0; i < SZ(init); i++) {
        lli eval = 0;
        for(int j = 0; j < SZ(cur); j++) {
            eval = (eval + init[i - j - 1] * cur[j] % mod) % mod;
        }

        eval -= init[i];
        if(eval) eval += mod;
        if(eval == 0) continue;
        if(cur.empty()) {
            cur.resize(i+1);
            m = i;
            ld = eval;
        } else {
            lli k = eval * inverse(ld, mod) % mod;
            vector<lli> c(i - m - 1);
            c.push_back(k);
            for(int j = 0; j < SZ(ls); j++) {
                c.push_back((mod - ls[j]) * k % mod);
            }

            if(SZ(c) < SZ(cur)) c.resize(cur.size());
            for(int j = 0; j < SZ(cur); j++) {
                c[j] += cur[j];
                if(c[j] >= mod) c[j] -= mod;
            }
            if(i - m + SZ(ls) >= SZ(cur))
                ls = cur, m = i, ld = eval;
            cur = c;
        }
    }

    if(cur.empty()) cur.push_back(0);
    reverse(all(cur));
    return cur;
}


vector<lli> get_dp(int n, const lli MOD) {
    vector<lli> coeffs = {2, MOD-1, 2, 1, 1, 0, MOD-1, MOD-1};

    vector<lli> dp = {1, 1, 1, 2, 6, 14, 28, 56};
    dp.resize(n+1);
    forr(i, 8, n) {
        forr(j, 1, 8) {
            lli ret = coeffs[j-1] % MOD * dp[i - j] % MOD;
            (dp[i] += ret) %= MOD;
        }
    }
    return dp;
}

vector<lli> get_DP_3(const vector<lli> &dp, const lli MOD) {
    int n = SZ(dp);
    vector<lli> S(n);
    for(int L = 0; L < n; L++) {
        if(L) S[L] = S[L-1];

        (S[L] += dp[L] * dp[L] % MOD * dp[L] % MOD) %= MOD;
    }
    return S;
}


vector<lli> get_coeffs_f3(int n, const lli MOD) {
    auto dp = get_dp(n, MOD);

    vector<lli> S(n+1);
    for(int L = 0; L <= n; L++) {
        if(L) S[L] = S[L-1];

        (S[L] += dp[L] * dp[L] % MOD * dp[L] % MOD) %= MOD;
    }

    return BerlekampMassey(S, MOD);
}

const int MOD_ANS = 1e9;
const lli BIG_MOD_1 = 1000000000000000000 - 11;
const lli BIG_MOD_2 = 100000000000000000 - 3;

int main() {

    const int n = 250;
    auto coeffs_mod_1 = get_coeffs_f3(n, BIG_MOD_1);
    auto coeffs_mod_2 = get_coeffs_f3(n, BIG_MOD_2);


    int m = SZ(coeffs_mod_1);
    vector<lli> real_coeffs(m);
    forn(i, m) {
        if(coeffs_mod_1[i] == coeffs_mod_2[i]) {
            real_coeffs[i] = coeffs_mod_1[i];
        } else {
            assert((coeffs_mod_1[i] - BIG_MOD_1) == (coeffs_mod_2[i] - BIG_MOD_2));
            real_coeffs[i] = (coeffs_mod_1[i] - BIG_MOD_1);
        }
    }


    forn(i, m) {
        real_coeffs[i] %= MOD_ANS;
        if(real_coeffs[i] < 0) real_coeffs[i] += MOD_ANS;
    }


    auto dp_1 = get_dp(m, MOD_ANS);
    auto DP_3 = get_DP_3(dp_1, MOD_ANS);


    ll N; cin>>N;
    
    cout << kthTermLinearRecurrence(real_coeffs, DP_3, N - 1, MOD_ANS) << endl;    
    
    

    return 0;
}