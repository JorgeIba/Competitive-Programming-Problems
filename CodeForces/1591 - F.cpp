#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


const lli MOD = 998244353;


int main () {
	//fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;


    
    vector<lli> dp(n+1);
    stack<pair<lli,lli>> st;

    dp[n] = 1;
    dp[n-1] = nums[n-1];
    st.push({nums[n-1], (n-1) & 1 ? -1 : 1});

    for(int Q = n-2; Q >= 0; Q--)
    {
        lli next_dp = Q & 1 ? dp[Q+1] : MOD-dp[Q+1];
        lli total = Q & 1 ? MOD-dp[Q+1] : dp[Q+1];

        while(!st.empty() && st.top().first > nums[Q])
        {
            ((next_dp -= st.top().first * st.top().second % MOD) += MOD) %= MOD;
            (total += st.top().second) %= MOD;

            st.pop();
        }


        dp[Q] = (nums[Q]*total % MOD + next_dp) % MOD;
        dp[Q] = Q & 1 ? MOD-dp[Q] : dp[Q];

        st.push({nums[Q], total});
    }


    cout << dp[0] % MOD << endl;

	return 0;
}

