#include<bits/stdc++.h> 
#define lli long long int
using namespace std; 
  
vector< pair<lli,lli> > points;
 
const lli MOD = 998244353;

vector<lli> fact(100010);
vector<lli> inverso(100010);

lli modulo(lli num)
{
    if(num >= 0)
    {
        return num%MOD;
    }
    else
    {
        return num % MOD + MOD;
    }
    
}

lli binPow(lli a, lli e)
{
    lli res = 1;
    a = a%MOD;
    while(e)
    {
        if(e&1) res = (res*a)%MOD;
        e >>= 1;
        a = (a*a)%MOD;
    }
    return res;
}

 
lli interpolacion(lli n)
{ 
    lli res = 0;
    for(int i = 1; i <= n; i++)
    {
        lli aux = ( (fact[n]*inverso[i] % MOD) *inverso[n-i])%MOD;
        //lli aux = fact[n]/(fact[i]*fact[n-i]);
        if(i%2 == 0) 
        {
            aux = -aux;
        }
        //res = modulo( modulo(res) *  modulo( aux*points[i-1].second ) );
        res = modulo( res + modulo(aux*points[i-1].second) ) ;
    }
    //cout<<res<<endl;
    return res;
} 
  
int main() 
{ 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    points.resize(n);
    
    fact[0] = 1;
    inverso[0] = 1;
    for(int i = 1; i<100010; i++)
    {
        fact[i] = i * fact[i-1] % MOD;
        inverso[i] = binPow(fact[i], MOD-2);
    }

    for(int i = 0; i< n; i++)
    {
        points[i].first = i+1;
        cin>>points[i].second;
    }

    lli res = interpolacion(n);
    lli minimo = min(1000LL, n);
    for(int i = 1; i<= minimo; i++)
    {
        if(res == interpolacion(i))
        {
            cout<<i<<" "<<res<<endl;
            return 0;
        }
    }
    return 0; 
} 