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


void main_(){
    int n, k; cin>>n>>k;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    vector< vector<lli> > cost_range(n+1, vector<lli>(n+1));

    for(int l = 0; l < n; l++){
        int white = 0, black = 0;
        for(int r = l; r < n; r++) {
            white += (nums[r] == 0);
            black += (nums[r] == 1);
            cost_range[l][r] = white * black;
        }
    }

    const int INF = 1e9;
    vector< vector<lli> > dp(n+1, vector<lli>(k+1, INF));
    vector< vector<int> > opt(n+1, vector<int>(k+1, -1));

    for(int l = 0; l < n; l++) {
        dp[l][1] = cost_range[l][n-1];
        opt[l][1] = n-1;
    }
    
    for(int j = 2; j <= k; j++) {
        for(int l = 0; l < n; l++) {
            int limit_l = l ? opt[l-1][j] : l;
            int limit_r = opt[l][j-1];
            for(int r = limit_l; r <= limit_r; r++){
                lli mn = cost_range[l][r] + dp[r+1][j-1];
                if(mn < dp[l][j]) {
                    dp[l][j] = mn;
                    opt[l][j] = r;
                }
            }
        }
    }

    // forr(l, 0, n-1) {
    //     forr(j, 1, k) {
    //         if(opt[l][j] == -1) continue;

    //         cout << opt[l][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << dp[0][k] << endl;
    return;
}


int main () {
	fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

