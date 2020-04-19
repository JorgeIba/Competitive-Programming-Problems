#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli res = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = i; j<n; j++)
        {
            res = max(res, nums[i]^nums[j]);
        }
    }
    cout<<res<<endl;
    return 0;
}