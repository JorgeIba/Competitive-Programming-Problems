#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const int MOD = 1e9+7;

/*
    O(n + t*n^(1/2))
    for(int i = 1; i<=a; i++)
    {
        for(int j = 1; j<=b; j++)
        {
            ans += i*j*f(__gcd(i,j));
        }
    }
*/

lli g(lli p, lli a)
{
    if(a == 1) return (p-1+MOD)%MOD;
    else if(a == 2) return (MOD-p)%MOD;
    return 0;
}

//35
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
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1) % MOD;
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p]%MOD;
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        b>>=1;
        a = (a*a)%MOD;
    }
    return res;
}

lli inv2 = binPow(2, MOD-2);

lli gauss(lli n)
{
    return (n*(n+1)%MOD) * inv2 % MOD;
}

const int maxN = 1e6+10;
auto f = sieveMulFunction(maxN);

int main () {
	fastIO();
    vector<lli> prefix(maxN);
    for(int i = 1; i<maxN; i++)
        prefix[i] = (prefix[i-1] + (f[i]*i%MOD*i%MOD))%MOD;


    lli t; cin>>t;

    while(t--)
    {
        lli a, b; cin>>a>>b;
        lli ans = 0;
        for(int i = 1, r; i<=min(a,b); i = r + 1)
        {
            lli la = a / i;
            lli ra = a / la; //[la, ra] same value
            lli lb = b / i;
            lli rb = b / lb; //[ra, rb] same value
            r = min(ra, rb);
            ans = (ans + (prefix[r] - prefix[i-1] + MOD)%MOD * gauss(la)%MOD * gauss(lb))%MOD;
        }
        cout << ans << endl;
    }
	return 0;
}