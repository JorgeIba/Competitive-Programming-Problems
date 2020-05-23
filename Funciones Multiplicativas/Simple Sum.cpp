#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res *= a;
        b>>=1;
        a*=a;
    }
    return res;
}


lli g(lli p, lli a)
{
    lli aux = (binPow(p,2*a) - 1) / (1+p) ;
    return 1 + aux*p;
}


vector<lli> sieve(lli n)
{
    vector<lli> primes, lp(n+1), cont(n+1), pot(n+1), f(n+1);
    f[1] = 1;
    for(int i = 2; i<=n; i++)
    {
        if(!lp[i])
        {
            lp[i] = pot[i] = i;
            cont[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes)
        {
            lli d = p * i;
            if(d>n) break;
            lp[d] = p;
            if(p==lp[i]) //gcd(i,p) = p;
            {
                f[d] = f[i/pot[i]] * g(p, 1 + cont[i]);
                cont[d] = cont[i] + 1;
                pot[d] = pot[i] * p;
                break;
            }
            else //gcd(i,p) = 1;
            {
                f[d] = f[i] * f[p];
                cont[d] = 1;
                pot[d] = p;
            }
        }
    }
    
    return f;
}



int main()
{
    fastIO();
    vector<lli> f = sieve(10000010);
    lli t; cin>>t;
    while(t--)
    {
        lli n; cin>>n;
        cout<<f[n]<<endl;
    }
    return 0;
}
