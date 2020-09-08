#include <bits/stdc++.h>
#define lli long long unsigned int
#define ulli __int128

using namespace std;


ulli expMod(ulli a, ulli e, ulli mod)
{
    ulli res = 1;
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
    lli b1, p1; cin>>b1>>p1;
    ulli b = __int128(b1), p = __int128(p1);
    

    if(__gcd(b,p) != 1) 
    {
        cout<<"no\n";
        return 0;
    }
    ulli x = p-1;
    while( (~x&1 ) )
    {
        if(expMod(b, x, p) == p-1)
        {
            cout<<"yes\n";
            return 0;
        }
        x>>=1;
    }
    if(expMod(b, x, p) == p-1)
        {
            cout<<"yes\n";
            return 0;
        }
    cout<<"no\n";
    
    return 0;
}