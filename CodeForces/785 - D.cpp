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

//13
const lli maxN = 1e6;
const lli MOD = 1e9+7; // Initialize
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
    if(r < 0 || n < 0 || r>n) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}


int main () {
	fastIO();
    prec();
    string s; cin>>s;
    int n = SZ(s);

    vector<lli> suffix(n+1);
    for(int i = n-1; i>=0; i--) suffix[i] = suffix[i+1] + (s[i] == ')');

    lli ans = 0, cnt = 0;
    for(int i = 0; i<n; i++)
    {
        if(s[i] == '(')
        {   
            cnt++;
            ans += nCr(cnt + suffix[i] - 1, cnt) % MOD;
            if(ans >= MOD) ans-=MOD;
        }
    }
    cout << ans << endl;
    

    
	return 0;
}