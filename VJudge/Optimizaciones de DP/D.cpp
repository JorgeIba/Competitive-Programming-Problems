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



/*
O(n^2 * k)
const lli INF = 1e18;
template<class G>
lli divide_and_conquer(int n, int k, G cost){
    vector< vector<lli> > dp(n+1, vector<lli>(k+1, INF));

    for(int l = 0; l < n; l++){
        dp[l][1] = cost(l, n-1);
    }
    dp[n][0] = 0;

    for(int j = 2; j <= k; j++){   
        for(int l = n-1; l >= 0; l--){
            for(int r = l; r < n; r++){
                dp[l][j] = min(dp[l][j], cost(l, r) + dp[r+1][j-1]);
            }
        }
    }

    return dp[0][k];
}
*/

// O(n*k*log(n))
const lli INF = 1e18;
vector<lli> dp_before, dp_curr;
template<class G>
void dac(int l, int r, int l_ans, int r_ans, G cost) {
    if(l > r) return;

    int mid = (l+r) / 2;

    // l_ans = max(mid, l_ans);
    int m_ans = l_ans;
    for(int i = l_ans; i <= r_ans; i++){
        if(cost(mid, i) + dp_before[i+1] < cost(mid, m_ans) + dp_before[m_ans+1]) {
            m_ans = i;
        }
    }
    dp_curr[mid] = cost(mid, m_ans) + dp_before[m_ans+1];

    dac(l, mid-1, l_ans, m_ans, cost);
    dac(mid+1, r, m_ans, r_ans, cost);
}

template<class G>
lli divide_and_conquer(int n, int k, G cost){
    dp_curr.resize(n+1);
    for(int l = 0; l < n; l++){
        dp_curr[l] = cost(l, n-1); // dp[l][1] -> 1 cut
    }
    dp_curr[n] = 0;

    for(int j = 2; j <= k; j++){
        dp_before = dp_curr;
        dac(0, n-1, 0, n-1, cost);
    }

    return dp_curr[0];
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

    cout << divide_and_conquer(n, k, cost) << endl;



	return 0;
}

