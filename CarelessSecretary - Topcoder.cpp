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

const lli maxN = 1e6+5;
const lli MOD = 1e9 + 7;
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

lli nCr(lli n, lli r)
{
    if(r < 0 || r > n) return 0;
    return fact[n]*invFact[r]%MOD*invFact[n-r]%MOD;
}

class CarelessSecretary
{
    public:
	int howMany(lli n, lli k)
    {
        prec();  
        lli ans = 0;
        for(int i = 1; i<=k; i++)
        {
            lli sign = ((i&1)?1:MOD-1);
            //cout << sign << " " << k << " " << i << " " << n-i << endl;
            ans += nCr(k, i)*fact[n-i]%MOD*sign%MOD;
            if(ans < 0) ans += MOD;
            else if(ans >= MOD) ans-=MOD;
        }
        return (fact[n] - ans + MOD)%MOD;
    }    	
};