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


const int MAXN = 55;
const int MAXM = 1e5 + 100;
const int MOD = 998244353;


vector<int> muSieve(int n){
	vector<int> Mu(n+1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}


lli dp[MAXN + 5][MAXM + 100];


int main () {
	fastIO();
	
    int n, m; cin>>n>>m;
    vector< pair<int,int> > limits(n);

    for(auto &[l, r]: limits) cin>>l>>r;

    auto mu = muSieve(MAXM);

    lli ans = 0;
    for(int d = 1; d <= m; d++) {
        for(int i = 0; i <= n + 1; i++) {
            for(int j = 0; j <= m/d + 1; j++) {
                dp[i][j] = 0;
            }
        }

        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            auto [l, r] = limits[i-1];

            int limit_l = (l + d - 1) / d;
            int limit_r = r / d;


            vector<lli> prefix_old_dp(m/d + 1);
            for(int j = 0; j <= m/d; j++) {
                lli acum = (j-1 >= 0 ? prefix_old_dp[j-1] : 0);
                prefix_old_dp[j] = (acum + dp[i-1][j]) % MOD;
            }

            for(int q = 0; q <= m/d; q++) { 
                // q * d == sum
                int pref_l = q - min(q, limit_r), pref_r = q - limit_l;
                if(pref_l > pref_r) continue;
                lli acum_l = (pref_l-1 >= 0 ? prefix_old_dp[pref_l - 1] : 0), acum_r = prefix_old_dp[pref_r];

                dp[i][q] += (acum_r - acum_l + MOD) % MOD;
                if(dp[i][q] < 0) dp[i][q] += MOD;
                if(dp[i][q] >= MOD) dp[i][q] -= MOD;
            }
        }

        lli ways_total = 0;
        for(int sum = 0; sum <= m/d; sum ++) {
            ways_total += dp[n][sum];
            if(ways_total >= MOD) ways_total -= MOD;
        }

        ans += mu[d] * ways_total % MOD;
        if(ans >= MOD) ans -= MOD;
        if(ans < 0)    ans += MOD;
    }

    cout << ans  << endl;

	return 0;
}

