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
const lli maxN = 1e6+100;
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


lli nCr(lli n, lli r) {
    if(n < 0 || r > n) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}


lli P(lli n, lli k) {
    lli ans = nCr(n+1, k+2) + nCr(n+1, k) - nCr(n-1, k) + MOD;
    return ans % MOD;
}


int main () {
	fastIO();

    prec();

    lli q; cin>>q;

    while(q--) {
        lli n, k, x; cin>>n>>k>>x;
        k--;
        lli ans = P(n, k);
        if(ans == x) {
            cout << "Correct\n";
        } else {
            cout << "Incorrect\n";
        }
    }

	return 0;
}

