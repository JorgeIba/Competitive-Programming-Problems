#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

const lli MOD = 1e9+7;

int main () {
	//fastIO();
	
	lli n, m; cin>>n>>m;

    lli ans = 0;
    for(int i = 0; i < n; i++){
        ans = (ans + powerMod(m, gcd(i, n), MOD)) % MOD;
    }

    ans = ans * powerMod(n, MOD-2, MOD) % MOD;
    cout << ans << endl;


	return 0;
}

