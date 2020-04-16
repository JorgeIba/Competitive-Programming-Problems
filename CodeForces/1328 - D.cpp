#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli contrario(lli n)
{
    if(n==1) return 2;
    if(n==2) return 1;
}

void solve()
{
    lli n; cin>>n;
    vector< vector<lli> > nums;
    nums.assign(n, vector<lli>(2));
    for(int i = 0; i<n; i++)
    {
        cin>>nums[i][0];
    }
    nums[0][1] = 1;
    for(int i = 1; i< n ; i++)
    {
        if(nums[i][0] == nums[i-1][0])
        {
            nums[i][1] = nums[i-1][1];
        }
        else
        {
            nums[i][1] = contrario(nums[i-1][1]);
        }
    }
    
    if(nums[n-1][0] == nums[n-2][0]   and  nums[n-1][0] == nums[0][0])
    {
        nums[n-1][1] = nums[0][1];
    }
    else
    {
        lli contrizq = contrario(nums[n-2][1]);
        lli contrder = contrario(nums[0][1]);
        if(contrizq == contrder)
        {
            if(contrizq == 1) nums[n-1][1] = 2;
            if(contrizq == 2) nums[n-1][1] = 1;
        }
        else
        {
            if(nums[n-1][0] == nums[n-2][0]) nums[n-1][1] = nums[n-2][1];
            else if(nums[n-1][0] == nums[0][0]) nums[n-1][1] = nums[0][1];
            else nums[n-1][1] = 3;
        }
    }
    


    lli res = -1;
    for(auto x: nums)
    {
        res = max(x[1], res);
    }
    cout<<res<<endl;
    for(auto x: nums)
    {
        cout<<x[1]<<" ";
    }
    cout<<endl;

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    lli q; cin>>q;
    while(q--) solve();
    return 0;
}