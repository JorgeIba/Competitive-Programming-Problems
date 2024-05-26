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

const int MOD = 1e9+7;
const int MAXN = 2e5 + 100;

lli powerMod(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

vector<lli> fact(MAXN + 1, 1), inv(MAXN + 1, 1), invFact(MAXN + 1, 1);
void prec() {
    for (lli i = 2; i <= MAXN; ++i) {
        fact[i] = i * fact[i - 1] % MOD;
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        invFact[i] = inv[i] * invFact[i - 1] % MOD;
    }
}
lli nCr(lli n, lli r) {
    if (n < 0 || r > n || r < 0)
        return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

const lli inv_2 = (MOD+1) / 2;
void main_(){
	int n, m, k; cin>>n>>m>>k;
    
    vector< int > score(m);
    forn(i, m){
        int u, v, x; cin>>u>>v>>x;
        score[i] = x;
    }

    auto Gauss = [&](lli n) {
        return n * (n+1) % MOD * inv_2 % MOD;
    };

    lli y = Gauss(n-1);


    lli A = 0, B = 0;
    for(int j = 0; j <= k; j++) {
        (A += nCr(k, j) * powerMod(y-1, k-j) % MOD * j % MOD) %= MOD;
        (B += nCr(k, j) * powerMod(y-1, k-j) % MOD * Gauss(j-1) % MOD ) %= MOD;
    }

    lli ans = 0;
    for(int i = 0; i < m; i++) {
        (ans += (1LL * score[i] * A) % MOD + B) %= MOD;
    }

    lli prob = powerMod(y, k);
    lli den = powerMod(prob, MOD-2);

    cout << ans * den % MOD << endl;



    // lli ans = 0;
    // for(int i = 0; i < m; i++) {
    //     auto x = score[i];
        
    //     lli sum = 0;
    //     for(int j = 0; j <= k; j++) {
    //         lli ways = nCr(k, j) * powerMod(y-1, k-j) % MOD;
    //         lli total_score = (x % MOD * j % MOD + Gauss(j-1)) % MOD;
    //         (sum += ways *  total_score % MOD) %= MOD;
    //     }

    //     (ans += sum) %= MOD;
    // }

    
    // lli prob = powerMod(y, k);
    // lli den = powerMod(prob, MOD-2);

    // cout << ans * den % MOD << endl;
}

int main () {
	// fastIO();

    prec();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

