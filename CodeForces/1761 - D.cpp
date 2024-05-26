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
vector<lli> pot3(maxN+1, 1);
void prec()
{
    pot3[1] = 3;
    for(lli i = 2; i <= maxN; ++i){
        pot3[i] = pot3[i-1] * 3 % MOD;
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}


lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


void solve(){

    prec();

    lli n, k; cin>>n>>k;

    if(k == 0) {
        cout << pot3[n] << endl;
        return;
    }

    lli ans = 0;
    for(int blocks = 1; blocks <= k; blocks++) {
        lli q = 2*blocks;

        lli ans_1 = 0, ans_2 = 0;
        if(n - q >= 0)
            ans_1 = pot3[n-q] * nCr(n-k, blocks) % MOD * nCr(k-1, k-blocks) % MOD;        

        if(n - q + 1 >= 0)
            ans_2 = pot3[n-q+1] * nCr(n-k, blocks-1) % MOD * nCr(k-1, k-blocks) % MOD;

        ans = (ans + ans_1 + ans_2) % MOD;
    }
	
    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	while(t--) solve();


	return 0;
}

