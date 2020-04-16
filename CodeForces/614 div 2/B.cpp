#include <bits/stdc++.h>
#define lli long long unsigned int

using namespace std;

void solve()
{
    lli A,B; cin>>A>>B;
    lli contador = 0;
    if(B >= 9)
    {
        contador=1;
    }
    if(B >= 99)
    {
        contador=2;
    }
    if(B >= 999)
    {
        contador=3;
    }
    if(B >= 9999)
    {
        contador=4;
    }
    if(B >= 99999)
    {
        contador=5;
    }
    if(B >= 999999)
    {
        contador=6;
    }
    if(B >= 9999999)
    {
        contador=7;
    }
    if(B >= 99999999)
    {
        contador=8;
    }
    if(B >= 999999999)
    {
        contador=9;
    }
    
    lli res = A * contador;
    cout<<res<<endl;
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