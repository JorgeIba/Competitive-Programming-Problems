#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli even = 0, odd = 0;
    for(auto x: nums)
    {
        if(x%2)
        {
            odd++;
        }
        else
        {
            even++;
        }
    }

    if(odd%2)
    {
        cout<<"YES\n";
        return;
    }
    if(odd == 0)
    {
        cout<<"NO\n";
        return;
    }

    else
    {
        if(even>0)
        {
            cout<<"YES\n";
        }
        else
        {
            cout<<"NO\n";
        }
        
    }
    
    



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