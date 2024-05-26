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


const lli INF = 1e18;
template<class G>
lli knuth_dp(int n, int k, G cost){
    vector< vector<lli> > dp(n+1, vector<lli>(k+1, INF));
    vector< vector<int> > opt(n+1, vector<int>(k+1, n-1));

    // Base cases
    for(int i = 0; i < n; i++){
        dp[i][1] = cost(i, n-1);
        opt[i][1] = n-1;
    }

    // Note we first iterate over cuts
    for(int j = 2; j <= k; j++){
        for(int l = 0; l < n; l++){
            int limit_l = (l ? opt[l-1][j] : 0);
            int limit_r = opt[l][j-1];
            
            for(int r = limit_l; r <= limit_r; r++){
                lli cost_range = cost(l,r) + dp[r+1][j-1];
                if(cost_range < dp[l][j]){
                    dp[l][j] = cost_range;
                    opt[l][j] = r;
                }   
            }
        }
    }
    
    // forr(l, 1, n-1){
    //     forr(j, 2, k) {
    //         if(opt[l][j] == INF) continue; // Valid Cut
    //         assert(opt[l-1][j] <= opt[l][j] && opt[l][j] <= opt[l][j-1]);
    //         // cout << opt[l][j] << " ";
    //     }
    //     // cout << endl;
    // }

    return dp[0][k];
}


int main () {
	//fastIO();
	
    int n, k; cin>>n>>k;
    vector<int> nums(n);

    for(auto &x: nums) cin>>x;

    vector<lli> prefix(n);
    forn(i, n){
        if(i) prefix[i] += prefix[i-1];
        prefix[i] += nums[i];
    }

    auto sum_range = [&](int l, int r) -> lli {
        return prefix[r] - (l? prefix[l-1] : 0);
    };

    auto cost = [&](int l, int r) -> lli {
        return (r - l + 1) * sum_range(l, r);
    };

    cout << knuth_dp(n, k, cost) << endl;



	return 0;
}

