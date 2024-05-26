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


//13
const lli maxN = 2e6;
const lli MOD = 235813; // Initialize
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


lli powerMod(lli a, lli b, lli mod){
    a %= MOD;
    if(a < 0) a += MOD;
    lli res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


int main () {
	//fastIO();
    prec();

    int n; cin>>n;
    vector<lli> nums(n);

    
    for(auto &x: nums) cin>>x;

    vector<lli> contribution(n);
    lli sum_total = 0;
    forn(i, n){
        int mult = (i & 1 ? -1 : 1);

        lli contr = mult * nCr(n-1, i) % MOD;

        sum_total = (sum_total + contr * nums[i] % MOD) % MOD;
        contribution[i] = contr;
    }

    const int LIMIT = 100'000;

    if(sum_total < 0) sum_total += MOD;

    int ans = 0;
    forn(i, n){
        lli new_sum_total = (sum_total - contribution[i] * nums[i] % MOD) % MOD; 

        if(new_sum_total < 0) new_sum_total += MOD;

        lli rhs = MOD - new_sum_total;
        rhs = rhs * powerMod(contribution[i], MOD-2, MOD) % MOD;
        lli opt_1 = rhs;
        lli opt_2 = rhs - MOD;


        if(abs(opt_1) <= LIMIT && opt_1 != nums[i]) {
            // cout << i << " ---> " << opt_1 << endl;
            assert((new_sum_total + contribution[i] * opt_1 % MOD) % MOD == 0);
            ans++;
            
        } else if(abs(opt_2) <= LIMIT && opt_2 != nums[i]) {
            // cout << i << " ---> " <<  opt_2 << endl;
            assert((new_sum_total + contribution[i] * opt_2 % MOD) % MOD == 0);
            ans++;
        } else {
            // cout << i << " NO SE PUEDE" << endl;
        }

    }

    cout << ans << endl;


	return 0;
}

