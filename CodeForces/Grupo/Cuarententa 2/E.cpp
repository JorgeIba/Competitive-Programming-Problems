#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

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

    lli l=0, r= 0, res = -1;
    lli numAnterior = -1;
    while(r<n)
    {
        if(nums[r] >= numAnterior)
        {
            lli size = r - l + 1;
            if(size > res)
            {
                res = size;
            }
            numAnterior = nums[r];
            r++;
        }
        else
        {
            l = r;
            numAnterior = nums[l];
        }
    
    }
    cout<<res<<endl;

}