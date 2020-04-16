#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;


void solve()
{
    lli a, b; cin>>a>>b;
    if(a==b)
    {
        cout<<0<<endl;
        return;
    }
    if(a>b)
    {
        if((a&1)and(b&1))
        {
            cout<<1<<endl;
        }
        else if((~a&1)and(~b&1))
        {
            cout<<1<<endl;
        }
        else
        {
            cout<<2<<endl;
        }
    }
    else
    {
        if((a&1)and(~b&1))
        {
            cout<<1<<endl;
        }
        else if((~a&1)and(b&1))
        {
            cout<<1<<endl;
        }
        else
        {
            cout<<2<<endl;
        }
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