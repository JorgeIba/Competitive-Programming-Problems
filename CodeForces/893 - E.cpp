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

vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}

const lli maxN = 2*1e6+10;
const lli MOD = 1e9+7;
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

map<lli,lli> factorize(lli n)
{
    map<lli,lli> fact;
    while(n>1)
    {
        lli lp = lowestPrime[n];
        while(n % lp == 0)
        {
            fact[lp]++;
            n /= lp;
        }
    }
    return fact;
}

lli nCr(lli n, lli r)
{
    if(r < 0 || r > n) return 0;
    return fact[n]*invFact[n-r]%MOD * invFact[r]%MOD;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a%MOD;
        b>>=1;
        a = a*a%MOD;
    }
    return res;
}

int main () {
	fastIO();
    lowestPrimeSieve(maxN);
    prec();

    lli t; cin>>t;
    while(t--)
    {
        lli X, Y; cin>>X>>Y;

        auto fact = factorize(X);
        lli ans = 1;
        for(auto x: fact)
        {
            //cout << x.first << " " << x.second << endl;
            ans = ans * nCr(x.second + Y - 1, Y-1) % MOD;
        }
        lli distr_neg = binPow(2, Y-1);

        //cout << ans << " " << distr_neg << endl;

        cout << ans*distr_neg%MOD << endl;
    }
    
    
	return 0;
}