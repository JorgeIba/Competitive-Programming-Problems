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


const lli MOD = 1e9+7;

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1; 
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

int main () {
	//fastIO();

    lli n; cin>>n;


    lli r0 = n*n;
    lli r1 = n*(n/2) - (n/2)*(n/2) + (n % 2);
    lli r2 = 2*n*(n/2) - 2*(n/2-1) * (n/2) - 2 * (n/2) + n%2;
    lli r3 = r1;

    
    lli ans = ( powerMod(2, r0, MOD) + powerMod(2, r1, MOD) + powerMod(2, r2, MOD) + powerMod(2, r3, MOD) ) % MOD * powerMod(4, MOD-2, MOD) % MOD;

    cout << ans << endl;
	

	return 0;
}

