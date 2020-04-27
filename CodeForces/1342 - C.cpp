#include <bits/stdc++.h>
#define lli long long int
using namespace std;


void solve()
{
    lli a, b, q; cin>>a>>b>>q;
    lli mcm = a * b / __gcd(a,b);
    if(a>b) swap(a,b);
    while(q--)
    {
        lli l, r; cin>>l>>r;
        lli cabel = (l-1)/mcm;
        lli caber = (r)/mcm;
        lli modulosl = max(0LL, (cabel-1)*(b-1));
        modulosl += min(cabel * mcm + b -1, l-1);
        modulosl = cabel*mcm - modulosl;
        lli modulosr = max(0LL, (caber-1)*(b-1));
        modulosr += min(caber * mcm + b -1, r);
        modulosr = caber*mcm - modulosr;
        lli modulos = modulosr - modulosl;
        lli res = (r-l+1) - modulos;
        cout<<res<<" ";
    }
    cout<<endl;
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