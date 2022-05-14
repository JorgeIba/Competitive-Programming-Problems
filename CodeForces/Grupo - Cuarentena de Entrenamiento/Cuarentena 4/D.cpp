#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    lli n, k; cin>>n>>k;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    if(k==1)
    {
        lli res = 100000000000LL;
        for(auto x: nums)
        {
            res = min(res, x);
        }
        cout<<res<<endl;
    }
    else if (k==2)
    {
        lli l = 0, r = n-1;
        lli res = max(nums[l], nums[r]);
        cout<<res<<endl;
    }
    else
    { 
        lli res = -100000000000LL;
        for(auto x: nums)
        {
            res = max(res, x);
        }
        cout<<res<<endl;
    }
    


    return 0;
}