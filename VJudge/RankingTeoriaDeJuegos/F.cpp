#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    lli res = 0;
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        res ^= x;
    }
    if(res==0)
    {
        cout<<"Second\n";
    }
    else
    {
        cout<<"First\n";
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