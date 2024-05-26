#include<bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl '\n'
#define forn(i, n) for(int i = 0; i < (n); i++) 
#define forr(i, a, b) for(int i = (a); i <= (b); i++) 
#define SZ(a) (int) a.size()
#define pb push_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;


int main() {
    // fastIO();

    int n; cin>>n;
    int q; cin>>q;

    int N = 1e4;
    const lli INF = 1e18;
    vector<lli> dp(N + 1 + 100, INF);
    for(int i = 1; i <= n; i++) {
        cin >> dp[i];
    }

    for(int i = n+1; i <= N+100; i++) {
        for(int k = 1; k <= i-1; k++) {
            dp[i] = min(dp[i], dp[k] + dp[i - k]);
        }
    }


    while(q--) {
        lli k; cin>>k;

        if(k <= N) {
            cout << dp[k] << endl;
            continue;
        } 

        lli ans = INF;
        for(auto LIMIT: {N-1, N, N+1}) {
            for(lli idx_min = 1; idx_min <= n; idx_min++) {
                lli q = (k - LIMIT) / idx_min;
                for(auto qq: {q-1, q, q+1}) {
                    lli aux_k = k;
                    aux_k -= idx_min*qq;
                    if(aux_k < 0 || aux_k > LIMIT) continue;
                    lli sum = dp[idx_min] * qq;
                    assert(sum < 1e18);
                    
                    lli mini = dp[aux_k];
                    ans = min(ans, sum + mini);
                }
                
            }
        }
        cout << ans << endl;
    }
    



    return 0;
}