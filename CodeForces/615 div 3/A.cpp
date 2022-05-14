#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n;
    vector<lli> asd(3);
    cin>>asd[0]>>asd[1]>>asd[2]>>n;
    sort(asd.rbegin(), asd.rend()); 
    lli diffAB = asd[0]-asd[1]; // O(cnt)
    lli diffAC = asd[0]-asd[2]; // O(cnt)
    if(n >= (diffAB+diffAC)) // O(cnt)
    {
        n -= (diffAB+diffAC); // O(cnt)
    }
    else
    {
        cout<<"NO\n"; //O(cnt)
        return;
    }

    if(n%3==0) // O(cnt)
    {
        cout<<"YES\n";
        return;
    }
    else
    {
        cout<<"NO\n";
    }

    // O(cnt) * O(cnt) = O(cnt^2) = O(cnt)

    // O(cnt)
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