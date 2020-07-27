#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    if(n&1)
    {
        cout<<-1<<endl;
        return;
    }
    sort(all(nums));
    for(int i = 1; i<=1024; i++)
    {
        bool flag = true;
        vector<lli> check(n);

        for(int j = 0; j<n; j++)
        {
            check[j] = nums[j] ^ i;
        }
        sort(all(check));
        for(int j = 0; j<n; j++)
        {
            if(check[j] != nums[j])
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            cout<<i<<endl;
            return;
        }
    }

    cout<<-1<<endl;
}

int main()
{
    fastIO();
    lli t; cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}