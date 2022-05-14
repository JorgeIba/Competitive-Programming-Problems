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
const lli maxN = 30;
const lli MOD = 1e9+7; // Initialize
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1), bernoulli(maxN+1, 1);

lli nCr(lli n, lli r)
{
    if(r < 0 || r > n) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}

void prec()
{
    for(lli i = 2; i <= maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
    }

    for(lli i = 1; i <= 20; i++)
    {
        lli sum = 0;
        for(lli k = 0; k < i; k++)
        {
            sum += nCr(i, k) * bernoulli[k] % MOD * inv[i-k+1] % MOD;
            if(sum >= MOD) sum -= MOD;
        }
        bernoulli[i] = (1 - sum + MOD) % MOD;
    }
}

lli binPower(lli a, lli b){
    lli res = 1;
    a %= MOD;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a*a % MOD;
    }
    return res;
}


lli getSum(lli m, lli k)
{
    lli sum = 0;
    for(lli j = 0; j <= k; j++)
    {
        lli sign = j & 1 ? MOD-1 : 1;
        sum += sign * nCr(k+1, j) % MOD * bernoulli[j] % MOD * binPower(m, k+1-j) % MOD;
        if(sum >= MOD) sum -= MOD;

    }
    return (sum * binPower(k+1, MOD-2) % MOD + binPower(m, k)) % MOD;
}



vector<lli> nums;
const lli maxROOT = 1e5+10;
lli dp[52][maxROOT];


lli f(lli m, lli n, lli k)
{
    if(m == 0) return getSum(n, k);

	if(n < maxROOT && dp[m][n] != -1) return dp[m][n]; 

    lli coprime = nums[m-1];
    lli before = f(m-1,  n, k);
    lli neww = f(m-1, n / coprime, k);
    lli pk = binPower(coprime, k);

	lli ans = (before -  pk * neww % MOD + MOD) % MOD;

	if(n < maxROOT) dp[m][n] = ans;

    return ans;
}



void solve()
{
    lli n, k, m; cin>>n>>k>>m;
	memset(dp, -1, sizeof(dp));

    nums.resize(n);
    for(auto &x: nums) cin>>x;
    cout << f(n, m, k) << endl;
}



int main () {
    fastIO();

    prec();

    lli t; cin>>t;

    while(t--) solve();


    return 0;
}

