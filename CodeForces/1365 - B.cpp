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
    vector<lli> types(n); 
    for(auto &x: nums)
    {
        cin>>x;
    }
    bool zero=false, one=false;
    for(auto &x: types)
    {
        cin>>x;
        if(x == 0) zero = true;
        else one = true;
    }
    vector<lli> aux = nums;
    sort(aux.begin(), aux.end());
    if(zero & one)
    {
        cout<<"Yes\n";
        return;
    }

    for(int i  = 0; i<n; i++)
    {
        if(aux[i] != nums[i])
        {
            cout<<"No\n";
            return;
        }
    }
    cout<<"Yes\n";

}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}