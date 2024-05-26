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


const int MOD = 998'244'353;

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

const int MAXN = 2e5 + 100, MAXP = 100 + 5;
int dp[MAXN][MAXP];
int main () {
	//fastIO();

    int inv_100 = powerMod(100, MOD-2);

    int n; cin>>n;
    vector< int > P(n+1), noP(n+1);

    forr(i, 1, n){
        cin>>P[i];
        P[i] = 1LL * P[i] * inv_100 % MOD;
        noP[i] = (1 - P[i] + MOD) % MOD;
    }

    // auto geometric = [&](int lower, int upper, int ratio){
    // };

    vector<int> E(n+1);
    E[0] = 0;

    for(int x = 1; x <= n; x++){
        int sum = 0;
        int P_or = 1LL * P[x] * 100 % MOD;


        for(int p_or = 0; p_or < 100; p_or++){
            int p = 1LL * p_or * inv_100 % MOD;

            int left = 1LL * dp[x-1][p_or] * p % MOD;
            int right = 1LL * p * p % MOD * E[x-1] % MOD;
            dp[x][p_or] = (left + right) % MOD;

            if(dp[x][p_or] >= MOD) dp[x][p_or] -= MOD;
        }

        sum = dp[x][P_or];
        // debugg(sum);

        // for(int i = 2; i <= x; i++){
        //     sum += 1LL * powerMod(P[x], i) * E[x + 1 - i] % MOD;
        //     if(sum >= MOD) sum -= MOD;
        // }    

        // debugg(x);
        // debugg(sum);

        E[x] = 1LL * (1 + sum) * powerMod(noP[x], MOD-2) % MOD;
    }

    int ans = 0;
    for(int x = 1; x <= n; x++) {
        ans += E[x];
        if(ans >= MOD) ans -= MOD;
    }
    // debugg(E[1]);
    // debugg(E[2]);

    cout << ans << endl;
	



	return 0;
}

