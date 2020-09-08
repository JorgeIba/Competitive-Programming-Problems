#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    lli res = 0;
    lli aux = 0;
    while(n>=10)
    { 
        aux = n%10;
        res += (n-aux);
        n /= 10;
        n+=aux;
    }
    res += n%10;
    cout<<res<<endl;
}


int main()
{
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}