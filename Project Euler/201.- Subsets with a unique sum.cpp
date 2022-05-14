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



const lli maxN = 100, maxK = 50, maxSUM = 297925;

vector<lli> a = {1, 3, 6, 8, 10, 11};


lli f(lli n)
{
    return (n+1)*(n+1);
}

int main () {
	//fastIO();

    time_t begin = clock();

    lli n = 100;
    lli k = 50;
    lli sum = maxSUM;


    vector<vector<lli>> old_dp(k+2, vector<lli>(sum+10));
    vector<vector<lli>> new_dp;

    old_dp[0][0] = 1;

    for(int i = 0; i < n; i++)
    {
        new_dp.assign(k+2, vector<lli>(sum+10));

        for(int j = 0; j <= k; j++)
        {
            for(int prev_sum = 0; prev_sum < sum; prev_sum++)
            {
                if(prev_sum + f(i) <= sum) 
                    new_dp[j+1][prev_sum + f(i)] += old_dp[j][prev_sum];

                new_dp[j][prev_sum] += old_dp[j][prev_sum];
            }
        }
        old_dp = new_dp;
    }


    vector<lli> ans;
    for(int i = 1; i <= sum; i++)
    {
        if(new_dp[k][i] == 1) ans.push_back(i);
        // cout << dp[n][3][i] << " ";
    }


    cout << SZ(ans) << endl;
    
    lli ans_sum = 0;
    for(auto x: ans) ans_sum += x;

    cout << ans_sum << endl;

    cout << "Time: " << (double) (clock() - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}

