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
	fastIO();

    int q, k; cin>>q>>k;
    
    vector<int> dp(k+1);
    dp[0] = 1;
    while(q--){
        char t; cin>>t;
        int x; cin>>x;
        if(t == '+'){
            for(int val = k - x; val >= 0; val--){
                dp[val + x] += dp[val];
                if(dp[val+x] >= MOD) dp[val+x] -= MOD;
            }
        } else {
            for(int val = 0; val <= k-x; val++){
                dp[val + x] -= dp[val];
                if(dp[val+x] < 0) dp[val+x] += MOD;
            }

        }
        cout << dp[k] << endl;
    }

	return 0;
}

