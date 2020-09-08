#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{
    fastIO();
    lli n; cin>>n;

    lli dp[n][n];

    vector<lli> nums(n);

    for(auto &x: nums)
    {
        cin>>x;
    }
    for(int L = n-1; L>=0; L--) 
    {
        for(int R = L; R<n; R++)
        {
            if(L==R) 
            {
                dp[L][R] = nums[L];
                continue;
            }
            dp[L][R] = max(nums[L] - dp[L+1][R],  nums[R] - dp[L][R-1]);
        }
    }

    cout<<dp[0][n-1]<<endl;
    return 0;
}