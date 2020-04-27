#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    vector<bool> flag(n, false);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli contador = 0, maximo = 0;
    for(int i = n-1; i>=0 ; i--)
    {
        maximo = max(maximo, nums[i]);
        if((nums[i] - contador) == 1LL)
        {
            contador = maximo;
            flag[i] = true;
        }
        else
        {
            if(i<(n-1))
            {
                if(nums[i] != (nums[i+1]-1))
                {
                    if(flag[i+1] == false)
                    {
                        cout<<"No\n";
                        return;
                    }
                }
            }
        }
    }
    cout<<"Yes\n";
    return;
}


int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    lli t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}