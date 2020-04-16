#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n;
    vector<lli> asd(3);
    cin>>asd[0]>>asd[1]>>asd[2]>>n;
    sort(asd.rbegin(), asd.rend());
    lli diffAB = asd[0]-asd[1];
    lli diffAC = asd[0]-asd[2];
    if(n>= (diffAB+diffAC))
    {
        n-= (diffAB+diffAC);
    }
    else
    {
        cout<<"NO\n";
        return;
    }

    if(n%3==0)
    {
        cout<<"YES\n";
        return;
    }
    else
    {
        cout<<"NO\n";
    }
    
    
    
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