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


const lli MOD = 1e9;
vector<lli> primes;

struct SumPrimes{
    vector<lli> poss_vals, dp;
    lli N, k, sqN, sz_vals;

    SumPrimes(lli N, lli k = 0): N(N), k(k), sqN(sqrt(N)) {
        poss_vals.reserve(2*sqN);
        for(lli i = 1; i <= sqN; i++) {
            poss_vals.push_back(i);
            if(N/i != i) poss_vals.push_back(N/i);
        }    
        sort(all(poss_vals), greater<lli>());
        sz_vals = SZ(poss_vals);
        dp.resize(sz_vals + 1);

        build(N);
    }

    lli powerSum(lli n) { 
        n %= MOD;
        if(k == 0) return n;
        else if(k == 1) return (n*(n+1)/2)%MOD; //! MOD
        else return -1;
    }

    lli getIdx(lli n){
        if (n <= sqN) return n - 1;
        else return  sz_vals - (N / n);
    }

    lli query(lli n) { return dp[getIdx(n)];}

    void build(lli N) {
        for(auto n: poss_vals) 
            dp[ getIdx(n)  ] = (powerSum(n)-1+MOD) % MOD;

        for(lli p = 2; p <= sqN; p++)
        {
            if(dp[ getIdx(p) ] == dp[ getIdx(p-1) ]) continue;
            lli p_k = p;

            primes.push_back(p);

            for(auto n: poss_vals) {
                if(p*p > n) break;
                lli ret = p_k*(dp[ getIdx(n / p) ] - dp[ getIdx(p-1) ]) % MOD;
                if(ret < 0) ret += MOD;

                dp[ getIdx(n) ] -= ret; 
                if(dp[getIdx(n)] < 0) dp[getIdx(n)] += MOD;
            }
        }
    }
};



SumPrimes *SP;

lli f(lli num, int idx_prime)
{
    lli ans = SP->query(num) - SP->query(primes[idx_prime]-1);
    if(ans < 0) ans += MOD;

    for(int next_idx = idx_prime; next_idx < SZ(primes); next_idx++) {
        lli p = primes[next_idx];
        if(p*p > num) break;
        ans += f(num/p, next_idx);
        if(ans >= MOD) ans -= MOD;
    }
    return ans;
}


int main () {
	//fastIO();

    lli n; cin>>n;

    time_t start = clock();
    SP = new SumPrimes(n, 1);

    cout << f(n, 0) << endl;
    cout << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

	return 0;
}

