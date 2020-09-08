#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n, k; cin>>n>>k;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    map<lli,lli> diff;
    for(int i = 0; i<n; i++)
    {
        diff[nums[i]]++;
    }
    if(diff.size() > k)
    {
        cout<<-1<<endl;
        return;
    }

    vector<lli> as;
    for(auto x: diff)
    {
        if(x.second > 0)
        {
            as.push_back(x.first);
        }
    }
    cout<<n*k<<endl;
    for(int i = 0; i<n*k; i++)
    {
        cout<<as[i%(as.size())]<<" ";
    }
    cout<<endl;
}




int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}