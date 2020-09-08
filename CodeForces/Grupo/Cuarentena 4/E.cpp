#include <bits/stdc++.h>
#define lli long long int
//#define endl "\n"

using namespace std;

lli n, m; 

lli dp[33][10100][33];

const lli MOD = 999999937;
vector<lli> residuos;

lli expMod(lli a, lli e, lli mod)
{
    lli res = 1;
    a = a % mod;
    while(e)
    {
        if(e&1) res = (res*a)%mod;
        e>>=1;
        a = (a * a)%mod;
    }
    return res;
}


lli funcion(lli index, lli rem, lli sizee)
{
    if(index >= ((sizee+1)/2))
    {
        if(rem==0) return 1;
        else return 0;
    }

    if(dp[index][rem][sizee] != -1)
    {
        return dp[index][rem][sizee];
    }
    
    lli ans = 0;

    for(lli i = 0; i<=9; i++)
    {
        if(index == 0 and i==0)
        {
            continue;
        }
        lli aux = funcion(index+1, (rem + (i*residuos[index]) +  (index!=(sizee-1-index)?(i*residuos[sizee-1-index]):0)  ) %m, sizee);
         
        ans = (ans + aux) % MOD ;
    }
    return dp[index][rem][sizee] =  ans%MOD;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));

    cin>>n>>m;

    residuos.resize(31);
    for(int i = 0; i<=30 ; i++)
    {
        residuos[i] = expMod(10, i, m);
    }
    
    lli aux = 0;
    for(int i = 1; i<=n; i++)
    {
        aux = (aux + funcion(0,0,i)) % MOD;
        //cout<<aux<<endl;
    }
    
    cout<<aux<<endl;
    
    
    return 0;
}

