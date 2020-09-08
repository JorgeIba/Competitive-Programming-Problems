#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector< lli > nums(n);
    for(auto &x: nums) cin>>x;
    vector< lli > ass(n);
    lli l = 0, r = n-1, cnt = 0;
    while(l<=r)
    {
        ass[l] = ass[r] = cnt ++;
        l++;
        r--;
    }

    for(int i = 0; i<n; i++)
    {
        if(ass[i] > nums[i])
        {
            cout <<"No\n"; return;
        }
    }

    if(n%2 == 0)
    {
        if(nums[n/2] > ass[n/2] || nums[n/2 - 1] > ass[n/2 - 1])
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
    else
    {
        cout << "Yes\n";
    }
    

    
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}