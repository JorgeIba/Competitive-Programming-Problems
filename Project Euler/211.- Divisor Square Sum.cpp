#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a;
        b>>=1;
        a = a*a;
    }
    return res;
}

lli g(lli p, lli a)
{
    return 1 + p*p*( (binPow(p, 2*a) - 1)/(p*p - 1)  );
}


vector<lli> sieveMulFunction(lli n)
{
    vector<lli> primes, lp(n+1), f(n+1), cnt(n+1), pot(n+1);
    f[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}

bool isPerfectSquare(lli n)
{
    ld sr = sqrt(n);
    return ( sr - floor(sr)  == 0);
}


int main()
{
    //fastIO();
    lli LIMIT = 64e6;
    vector< lli > sigma2 = sieveMulFunction(LIMIT);
    lli suma = 0;
    for(lli i = 1; i<LIMIT; i++)
    {
        if( isPerfectSquare( sigma2[i] ) )
        {
            suma += i;
            //cout << "Smn " << sigma2[i] << endl;
        }   
    }
    cout << suma << endl;



    return 0;
}