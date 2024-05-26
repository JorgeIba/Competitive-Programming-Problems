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

vector<lli> primes;

lli binPower(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b & 1) res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}

// Calculate 2^k + 3^k + 5^k + ...
// For each value floor(N/i)
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
        if(k == 0) return n;
        else if(k == 1) return n*(n+1)/2; //! MOD
        else return -1;
    }

    lli getIdx(lli n){
        if (n <= sqN) return n - 1;
        else return  sz_vals - (N / n);
    }

    lli query(lli n) { return dp[getIdx(n)];}

    void build(lli N) {
        for(auto n: poss_vals) 
            dp[ getIdx(n)  ] = powerSum(n)-1;

        for(lli p = 2; p <= sqN; p++)
        {
            if(dp[ getIdx(p) ] == dp[ getIdx(p-1) ]) continue;

            primes.push_back(p);
            lli p_k = binPower(p, k);

            for(auto n: poss_vals) {
                if(p*p > n) break;
                dp[ getIdx(n) ] -=  p_k*(dp[ getIdx(n / p)] - dp[ getIdx(p-1) ]); //! MOD
            }
        }
    }
};

const lli maxN = 1e14;
const lli maxSQRT = sqrtl(maxN)+5;

lli getMaxExponent(lli p, lli n) {
    lli max_exponent = 0, div = n;
    // cout << "2 " << n << " " << maxN << " " << num << endl;
    while(div/p > 0) div /= p, max_exponent++;
    return max_exponent;
}

SumPrimes *P;


// unordered_map<lli,lli> dp2[10000];
lli f(lli N) {

    vector<lli> poss_vals;
    for(lli i = 1; i*i <= N; i++) {
        poss_vals.push_back(i);
        if(N/i != i) poss_vals.push_back(N/i);
    }

    sort(all(poss_vals));

    unordered_map<lli,lli> dp2, dp1;

    for(int idx = SZ(primes)-1; idx >= 0; idx--) {
        auto p = primes[idx];

        for(auto n_val: poss_vals) {
            if(p*p > n_val) continue;

            lli max_exponent = getMaxExponent(p, n_val);

            lli si = 0, no = dp2[n_val];
            for(lli e = 1, power = p; e <= max_exponent; power *= p, e++) {
                if( power > n_val/p) break;

                lli mult = (1LL << e);

                si += mult * dp2[n_val/power];

                lli U = P->query(n_val / power);
                lli L = P->query(p) - 1;

                lli primes_diff = U-L;

                si += mult * 2 * primes_diff;
            }
            dp1[n_val] = si+no;
        }
        dp2 = dp1; 
    }
    return dp1[N];
}


int main () {
	//fastIO();

    lli n = 1e14;

    time_t start = clock();

    P = new SumPrimes(n);

    cout << (ld)(clock() - start)/CLOCKS_PER_SEC << endl;
    start = clock();

    // lli ans = 2*P->query(n);
    // ans += dfs(0, n);
    

    cout << f(n) + 1 + 2*P->query(n) << endl;

    // cout << ans + 1 << endl;
    cout << (ld)(clock() - start)/CLOCKS_PER_SEC << endl;
    
    // ans = 28874142998632109
    // 25763 secs


	return 0;
}

