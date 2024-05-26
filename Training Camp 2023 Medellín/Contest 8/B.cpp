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


const lli MAXN = 5e3 + 1000;
const lli MOD = 998244353;
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


int main () {
	//fastIO();
	
    prec();

	lli G, B, R; cin>>G>>B>>R;
    
    // lli ans = 0;
    // for(int b = 0; b <= B; b++){
    //     for(int r = 0; r <= R; r++){
    //         for(int r_2 = 0; r_2 <= R; r_2++){
    //             ans += nCr(G, b) * nCr(B, b) * fact[b] * nCr(G, r) * nCr(R, r) * fact[r] * nCr(B, r_2) * nCr(R, r_2) * fact[r_2];
    //         }
    //     }
    // }

    lli ans_1 = 0;
    for(int b = 0; b <= B; b++){
        for(int r = 0; r <= R; r++){
            ans_1 += nCr(G, b) * nCr(B, b) % MOD * fact[b] % MOD * nCr(G, r) % MOD * nCr(R, r) % MOD * fact[r] % MOD;
            ans_1 %= MOD;
        }
    }

    lli ans_2 = 0;
    for(int r_2 = 0; r_2 <= R; r_2++){
        ans_2 += nCr(B, r_2) * nCr(R, r_2) % MOD * fact[r_2] % MOD;
        ans_2 %= MOD;
    }

    cout << ans_1 * ans_2 % MOD << endl;


	return 0;
}

