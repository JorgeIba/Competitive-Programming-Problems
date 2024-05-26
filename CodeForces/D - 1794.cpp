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

const lli maxA = 2e6+100;
const lli MOD = 998244353; 
vector<lli> fact(maxA+1, 1), inv(maxA+1, 1), invFact(maxA+1,1);
void prec()
{
    for(lli i = 2; i <= maxA; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}


//20
vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


lli total = 1;

vector<int> nums;
vector<int> primesD;
int n; 
int fr[maxA];

const int MAXN = 2022;

lli dp[2*MAXN+10][MAXN+20];

lli f(int idx, int chosen) {
    if(chosen == n) return total;
    if(idx == SZ(primesD)) {
        return 0;
    }

    lli &ans = dp[idx][chosen];
    if(ans != -1) return ans;

    ans = 0;

    auto p = primesD[idx];

    ans = (f(idx+1, chosen) + f(idx+1, chosen + 1) * fr[p] % MOD) % MOD;
    return ans;
}


int main () {
	fastIO();
	prec();
    primesSieve(maxA);

    cin>>n;
    nums.resize(2*n);
    for(auto &x: nums) cin>>x;

    for(auto x: nums) fr[x]++;

    for(int i = 1; i < maxA; i++) {
        if(isPrime[i] && fr[i]) {
            primesD.push_back(i);
        }
    }

    for(int i = 1; i < maxA; i++) {
        total = total * invFact[fr[i]] % MOD;
    }

    total = total * fact[n] % MOD;

    memset(dp, -1, sizeof(dp));    
    lli ans = f(0, 0);

    cout << ans << endl;


	return 0;
}

