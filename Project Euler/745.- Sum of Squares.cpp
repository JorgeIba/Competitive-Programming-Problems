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

const lli maxN = 1e7+10;
const lli MOD = 1e9+7;

lli g(lli p, lli k)
{
    return (MOD-1) * (k == 1);
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
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1) % MOD;
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p] % MOD;
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}



auto miu = sieveMulFunction(maxN);

lli F(lli n)
{
    lli ans = 0;
    for(lli i = 1; i*i <= n; i++)
    {
        lli aux = miu[i] * ((n / (i*i)) % MOD) % MOD;
        ans = (ans + aux)%MOD;
    }
    return ans;
}


lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b>>=1;
        a = a*a%MOD;
    }
    return res;
}

lli inv6 = binPow(6, MOD-2);

lli Gauss2(lli n)
{
    n %= MOD;
    return n * (n+1) % MOD * (2*n + 1) % MOD * inv6 % MOD;
}


int main () {
	//fastIO();

    
    lli n; cin>>n;

    
    lli ans = 0;
    for(lli i = 1, r; i*i <= n; i = r+1)
    {
        r = n/(n/i);
        
        ans += (Gauss2(r) - Gauss2(i-1) + MOD) % MOD * F(n/(i*i)) % MOD;
        if(ans >= MOD) ans -= MOD;
    }

    cout << ans << endl;
    
    
	return 0;
}