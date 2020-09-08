#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli factorial[1000005];
lli inverse[1000005];
const lli MOD = 998244353;

lli binPow(lli a, lli e)
{
    lli res = 1;
    a %= MOD;
    while(e)
    {
        if(e&1) res = (res * a) % MOD;
        e>>=1;
        a = (a*a) %MOD;
    }
    return res;
}


void inicializar()
{
    factorial[0] = inverse[0] = 1;
    for(int i=1; i<1000001; i++)
    {
        factorial[i] = factorial[i-1]*i % MOD;
        inverse[i] = binPow(factorial[i], MOD-2);
    }
}

lli comb(lli n, lli i)
{
    return (((factorial[n]*inverse[i])%MOD)*inverse[n-i])%MOD;
}


int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    inicializar();

    lli n, x, a, b; cin>>n>>x>>a>>b;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    for(int i = 0; i<n; i++)
    {
        if(nums[i] < a)
        {
            x = x-(a-nums[i]);
            nums[i] = a;
        }
    }
    if(x<0)
    {
        cout<<0<<endl;
        return 0;
    }
    cout<<x<<endl;
    for(auto x: nums)
    {
        cout<<x<<" ";
    }


   


    return 0;
}