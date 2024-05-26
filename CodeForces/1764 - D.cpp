#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;


//13
const lli maxN = 1e6;
lli MOD = 1;
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
    if(n < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


void main_(){
    lli n, p; cin>>n>>p;
    MOD = p;
    prec();

    lli ans = 0, t = n/2;
    for(lli k = t; k <= n-2; k++) {
        for(lli i = 0; i <= n-k-2; i++) {
            ans += (2*t-k) * nCr(n-k-2, i) % MOD * fact[i + k - 1] % MOD;
        }
    }

    ans += (n % 2 == 0 ? fact[n-2] : 0);
    if(ans >= MOD) ans -= MOD;

    cout << n * ans % MOD << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	// cin>>t;
	while(t--) 
		main_();


	return 0;
}

