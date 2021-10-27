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


const lli MOD = 1e9;

lli gauss2(lli n)
{
    lli a = n, b = n+1, c = 2*n+1;

    if(a % 2 == 0) a /= 2;
    else if(b % 2 == 0) b /= 2;
    else c /= 2;

    if(a % 3 == 0) a /= 3;
    else if(b % 3 == 0) b /= 3;
    else c /= 3;

    a %= MOD, b %= MOD, c %= MOD;

    return a * b % MOD * c % MOD;
}


int main () {
	//fastIO();

    //lli n; cin>> n;
    lli n = 1e15;

    lli ans = 0;
    
    for(lli i = 1, r = 0; i <= n; i = r+1)
    {
        r = n/(n/i);
        lli sum = (gauss2(r)%MOD - gauss2(i-1)%MOD + MOD) % MOD;
        assert( 0 <= sum && sum < MOD );
        lli howMuch = (n/i) % MOD;
        ans += (sum * howMuch)%MOD;
        if( ans >= MOD) ans -= MOD;
    }
	
    cout << ans << endl;

	return 0;
}

