#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli expMod(lli a, lli e, lli mod)
{
    lli res = 1;
    a %= mod;
    while(e)
    {
        if(e&1) res = (res*a)%mod;
        e>>=1;
        a = (a * a)%mod;
    }
    return res;
}


int main()
{
    lli b, mod,e;
    while(true)
    {
        cin>>b>>e>>mod;
        cout<<expMod(b,e,mod)<<endl;
    }

    return 0;
}