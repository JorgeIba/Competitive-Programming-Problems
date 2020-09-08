#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    map<lli,lli> last;
    map<lli,lli> first;
    for(auto &x: nums)
    {
        cin>>x;
    }

    for(int i = 0; i<n; i++ )
    {
        if(first.find(nums[i]) == first.end() )
        {
            first[nums[i]] = i;
        }
    }

    for(int i = n-1; i>=0; i--)
    {
        if(last.find(nums[i]) == last.end())
        {
            last[nums[i]] = i;
        }
    }
    
    for(auto x: first)
    {
        if( x.second < last[x.first] - 1)
        {
            cout<<"YES\n";
            return;
        }
    }
    cout<<"NO\n";
}


int main()
{
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}