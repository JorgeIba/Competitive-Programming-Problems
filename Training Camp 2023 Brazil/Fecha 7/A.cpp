#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

//13
const lli maxN = 3e5;
const lli MOD = 1e9+7;
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i <= maxN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

int main () {
	//fastIO();
	
	prec();

    lli n, m; cin>>n>>m;

    lli ans = 0;
    for(int pairs = 0; pairs <= n; pairs++) {
        ans += nCr(m+1, pairs) * nCr(m+1 - pairs, n-2*pairs) % MOD;
        if(ans >= MOD) ans -= MOD;
    }
    cout << ans << endl;


	return 0;
}

