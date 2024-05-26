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


const int MAXN = 15 + 1;
int dp[MAXN+5][(1 << MAXN) + 5];

int main () {
	fastIO();

    int n, m; cin>>n>>m;
    vector<int> caps(n), weights(m);

    for(auto &x: caps) cin>>x;
    for(auto &x: weights) cin>>x;


    vector<int> sum_mask(1 << m);
    for(int mask = 0; mask < (1 << m); mask++){
        int sum = 0;
        for(int j = 0; j < m; j++){
            if(mask & (1 << j))
                sum += weights[j];
        }
        sum_mask[mask] = sum;
    }

    for(int mask = 0; mask < (1 << m); mask++){
        dp[n][mask] = m - __builtin_popcount(mask);
    }

    for(int man = n-1; man >= 0; man--) {
        for(int mask = 0; mask < (1 << m); mask++) {
            for(int submask = mask; submask; submask = (submask - 1) & mask) {
                if(caps[man] >= sum_mask[submask]) {
                    dp[man][mask] = max(dp[man][mask], dp[man+1][mask ^ submask]);
                }
            }
            dp[man][mask] = max(dp[man][mask], dp[man+1][mask]);
        }
    }
    cout << dp[0][(1 << m) - 1] << endl;



	return 0;
}

