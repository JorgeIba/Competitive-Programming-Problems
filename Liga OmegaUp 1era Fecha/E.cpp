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


const lli INF = 1e18;


vector<lli> nums;

const lli maxN = 1e6+10;
lli dp[maxN][2];


lli f(lli idx, lli sum)
{
    if(idx == SZ(nums)) 
    {
        return sum % 2 == 0 ? -INF : 0;
    }


    lli &ans = dp[idx][sum];
    if(ans != -1) return ans;

    lli num = nums[idx];

    lli si = f(idx+1, (sum + num)%2) + num;
    lli no = f(idx+1, sum);


    return ans = max(si, no);
}


int main () {
	//fastIO();

    memset(dp, -1, sizeof(dp));
    lli n; cin>>n;
    nums.resize(n);
    for(auto &x: nums) cin>>x;


    lli ans = 0;
    for(int i = 0; i<n; i++)
    {
        ans = max(ans, f(i+1, nums[i] % 2) + nums[i]);
    }

    cout << ans << endl;
    

	return 0;
}

