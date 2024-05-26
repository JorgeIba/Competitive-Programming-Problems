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

const int MOD = 998244353;

int main () {
	//fastIO();
    int n, k; cin>>n>>k;


    vector< vector<int> > dp_old(k, vector<int>(n/k+1));
    dp_old[0][0] = 1;


    for(int i = 1; i <= n; i++){
        vector< vector<int> > dp_new(k, vector<int>(n/k+1));
        for(int points = 0; points <= n/k; points++){

            // SUFFIX
            vector<int> suffix_dp(k);
            for(int j = k-1; j >= 0; j--){
                if(j+1 < k)
                    suffix_dp[j] = suffix_dp[j+1];


                suffix_dp[j] += dp_old[j][points];
                if(suffix_dp[j] >= MOD) suffix_dp[j] -= MOD;
            }


            // DP_NEW
            for(int suffix = 0; suffix <= k-1; suffix++){
                if(suffix == 0){
                    // diff
                    if(points){
                        dp_new[0][points] += dp_old[k-1][points-1];
                        if(dp_new[0][points] >= MOD) dp_new[0][points] -= MOD;
                    }
                } else{ 
                    // diff
                    dp_new[suffix][points] += 1LL * (k - (suffix - 1)) * dp_old[suffix-1][points] % MOD;
                    if(dp_new[suffix][points] >= MOD) dp_new[suffix][points] -= MOD;

                    // equal
                    dp_new[suffix][points] += suffix_dp[suffix];
                    if(dp_new[suffix][points] >= MOD) dp_new[suffix][points] -= MOD;
                    // for(int j = suffix; j <= k-1; j++){
                    //     dp_new[suffix][points] += dp_old[j][points];
                    // }
                }
            }
        }
        dp_old = dp_new;
    }

    lli ans = 0;
    for(int i = 1; i <= n/k; i++){
        lli sum = 0;
        for(int j = 0; j <= k-1; j++){
            sum += dp_old[j][i];
        }
        ans += sum * i % MOD;
        if(ans >= MOD) ans -= MOD;
    }

    cout << ans << endl;
    

	return 0;
}

