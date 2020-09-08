#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector<lli> ans(n), nums(n);

    for(auto &x: nums)
    {
        cin>>x;
    }
    sort(nums.begin(), nums.end());
    lli l = 0, r = n-1, cont = 0;
    while(l<=r)
    {
        if(cont%2==0)
        {
            ans[cont] = nums[l++];
        }
        else
        {
            ans[cont] = nums[r--];
        }
        cont++;
    }
    reverse(ans.begin(), ans.end());
    for(auto x: ans)
    {
        cout<<x<<" ";
    }
    cout<<endl;


}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;   
}