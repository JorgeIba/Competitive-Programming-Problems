#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli g(lli p, lli a)
{
    //return binPow(p, a-1) * (p-1);
    return -1 * (a == 1);
}

vector<lli> sievePhi(lli n)
{
    vector<lli> primes, lp(n+1), f(n+1), cnt(n+1), pot(n+1);
    f[1] = 1;
    for(int i = 2; i<=n; i++)
    {
        if(!lp[i])
        {
            lp[i] = pot[i] = i; cnt[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes)
        {
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]) // lowestPrime[i] == p
            {
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else //Coprimes
            {
                f[d] = f[i]*f[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}


const lli MAXN = 4000010;

int main()
{
    fastIO();
    vector<lli> a = sievePhi(MAXN);
    lli n, count = 0; cin>>n;
    for(int i = 2; i<=MAXN-10; i++)
    {
        if(a[i]==1) 
        {
            count++;
        }
        if(count==n)
        {
            cout<<i<<endl;
            return 0;
        }
    }

    return 0;
}