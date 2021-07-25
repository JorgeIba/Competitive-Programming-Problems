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

vector<lli> nums;


lli w(lli l, lli r)
{
    lli sum = 0;
    for(int i = l; i<=r; i++)
    {
        for(int j = i+1; j<=r; j++)
        {
            sum += nums[i]*nums[j];
        }
    }
    return sum;
}

lli dp[3][3];

int main () {
	//fastIO();
    lli n; cin>>n;

    nums.resize(n);
    
    for(auto &x: nums)
    {
        cin>>x;
        x %= 3;
    }

    
    vector<lli> prefix_sum(n), prefix_sq(n);
    for(int i = 0; i<n; i++)
    {
        prefix_sum[i] = ((i? prefix_sum[i-1] : 0) + nums[i])%3;
        prefix_sq[i] = ((i? prefix_sq[i-1] : 0) + nums[i]*nums[i])%3;
    }


    dp[0][0] = 1;

    
    lli ans = 0;
    for(int i = 0; i<n; i++)
    {
        lli S_i = prefix_sum[i], T_i = prefix_sq[i];
        for(int x = 0; x<3; x++)
        {
            for(int y = 0; y<3; y++)
            {
                if(((S_i - x + 3)*(S_i - x + 3)) % 3 == (T_i - y + 3)%3)
                {
                    ans += dp[x][y];
                }
            }
        }
        dp[S_i][T_i]++;
    }  

    cout << ans << endl;
	return 0;
}

