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


const int MAXN = 3e5+100;
const int MAXANS = 9;
const int MOD = 998244353;

lli fact[MAXN], invFact[MAXN], inv[MAXN];
void prec(){
    fact[0] = fact[1] = invFact[0] = invFact[1] = inv[0] = inv[1] = 1;

    for(lli i = 2; i < MAXN; ++i){
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

    int n; cin>>n;
    vector<int> a(n);

    int gcd_ = 0;
    for(auto &x: a) {
        cin>>x;
        gcd_ = gcd(x, gcd_);
    }

    if(gcd_ > 1) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> fr(MAXN);
    for(auto x: a) fr[x] = 1;

    vector< int > divisible(MAXN);
    for(int i = 1; i < MAXN; i++){
        for(int j = i; j < MAXN; j += i){
            divisible[i] += fr[j];
        }
    }


    vector< array<int, MAXANS> > dp(MAXN);

    for(int ans = 1; ans < MAXANS; ans++){

        for(int g = MAXN - 1; g >= 1; g--){

            dp[g][ans] = nCr(divisible[g], ans);

            for(int k = 2*g; k < MAXN; k += g){
                dp[g][ans] -= dp[k][ans];
                if(dp[g][ans] < 0) dp[g][ans] += MOD;
            }
        }

        if(dp[1][ans] > 0){
            cout << ans << endl;
            return 0;
        }
    }




	return 0;
}

