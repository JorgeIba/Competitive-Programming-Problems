#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())



using namespace __gnu_pbds;

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


VLL sieveMiu(lli n) {
    VLL miu(n+1, -1);
    miu[0] = 0, miu[1] = 1;

    for(lli i = 2; i <= n; i++) {
        if(miu[i]) {
            for(lli j = 2*i; j <= n; j += i) {
                miu[j] -= miu[i];
            }
        }
    }
    return miu;
}

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



const lli MOD = 1e9+7;
vector<lli> Bern;
vector<lli> fact, inv, invFact;


void precFact(lli n) {
    fact.assign(n+1, 1), inv.assign(n+1, 1), invFact.assign(n+1, 1);
    for(lli i = 2; i <= n; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}

void precBern(lli N) {
    Bern.resize(N+1);
    Bern[0] = 1;
    for(int n = 1; n <= N; n++) {
        lli sum = 0;
        for(int k = 0; k <= n-1; k++) {
            sum += nCr(n, k) * Bern[k] % MOD * inv[n - k + 1] % MOD;
            if(sum >= MOD) sum -= MOD;
        }
        Bern[n] = (1 - sum + MOD) % MOD;
    }
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    a %= mod;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

// sum(1^k + 2^k + ... + n^k)
lli S(lli n, lli k) {
    lli sum = 0;
    for(int i = 0; i <= k; i++) {
        sum += nCr(k+1, i) * Bern[i] % MOD * powerMod(n, k + 1 - i, MOD) % MOD;
        if(sum >= MOD) sum -= MOD;
    }
    return inv[k+1] * sum % MOD;
}

const lli maxM = 1e6+5;
auto miu = sieveMiu(maxM);


gp_hash_table<lli, lli> dpU[51]; // va a madres

lli getSumSquareFreeK(lli n, lli k) {
    if(dpU[k].find(n) != dpU[k].end()) return dpU[k][n];

    lli sum = 0;
    for(lli x = 1; x*x <= n; x++) {
        lli term = powerMod(x*x % MOD, k, MOD) * S(n / (x*x), k) % MOD;
        sum = (sum + miu[x]*term % MOD + MOD) % MOD;
    }
    return dpU[k][n] = sum;
}



lli g(lli p, lli a, lli k) {
    lli p_k = powerMod(p, k, MOD);
    lli num = (1 - powerMod(MOD-p_k, a-1, MOD) + MOD) % MOD;
    lli den = powerMod(p_k+1, MOD-2, MOD);
    lli fracc = num * den % MOD;
    return p_k * fracc % MOD;
}


vector<lli> ans(51);


void bfs(lli N, lli k) {


    queue<tuple<lli,lli, lli>> q;
    q.push({-1, 1, 1});  // primes[-1] = 1

    
    while(!q.empty()) {
        auto [idx, num, f_num] = q.front(); q.pop();

        lli U = getSumSquareFreeK(N/num, k);
        
        ans[k] += f_num * U % MOD;
        if(ans[k] >= MOD) ans[k] -= MOD;

        lli n = N/num;
        
        for(int y = idx+1, p_next = primes[y]; y < SZ(primes) && n >= p_next*p_next; p_next = primes[++y]) {
            
            for(lli e = 2, power = p_next; power <= n/p_next; e++) {
                power *= p_next;
                q.push({y, num*power, f_num * g(p_next, e, k) % MOD});
            }
        }
    }

    return;
}


int main () {
	//fastIO();

    time_t start = clock();

    lli n = 1e12, K = 50;

    primesSieve(sqrtl(n)+1);
    precFact(200);
    precBern(200);


    lli ansS = 0;
    for(int k = 1; k <= K; k++) {
        bfs(n, k);
        cout << k << endl;
        ansS += ans[k];
        if(ansS >= MOD) ansS -= MOD;
    }
    

    cout << ansS << endl;
    cout << (ld)(clock()-start)/CLOCKS_PER_SEC << endl;


    


    /*
    auto h = sieveMulFunction(n+1);

    for(lli i = 1; i <= n; i++) {
        (sum += h[i] * getSumSquareFreeK(n/i, 1) % MOD) %= MOD;
    }
    
    cout << sum << endl;
    */



    

	return 0;
}

