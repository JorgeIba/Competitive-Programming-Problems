#include <bits/stdc++.h>
#define lli long long int

using namespace std;

const lli INF = 10000000000LL;

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    vector<lli> deber(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli mayorAnterior = -INF;
    for(int i = 0; i<n; i++)
    {
        if(nums[i] < mayorAnterior)
        {
            deber[i] = mayorAnterior - nums[i];
        }
        else
        {
            mayorAnterior = nums[i];
        }
        
    }
    lli mayor = -INF;
    for(auto x: deber)
    {
        mayor = max(mayor, x);
    }
    if(mayor == 0)
    {
        cout<<0<<endl;
    }
    else
    {
        lli res = log2(mayor) + 1;
        cout<<res<<endl;
    }
    
    



}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //cout<<(lli)(log2(4))<<" "<<(lli)(log2(5))<<" "<<(lli)(log2(8))<<endl;
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;   
}