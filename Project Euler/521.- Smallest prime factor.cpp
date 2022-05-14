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


lli MOD = 1e9;

lli binPower(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b & 1) res = res * a % MOD;
        b >>= 1;
        a = a*a % MOD;
    }
    return res;
}


vector<lli> primes;
lli ans_low = 0;

struct SumPrimes{
    vector<lli> poss_vals, dp, dp2;
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
        dp2.resize(sz_vals + 1);

        build(N);
    }


    lli powerSum(lli n) { 
        if(k == 0) return n;
        else if(k == 1) 
        {
            if( n & 1 ) return (n % MOD) * (((n+1)/2) % MOD) % MOD;
            else return ((n/2) % MOD)*((n+1) % MOD) % MOD;
        }
        else return -1;
    }

    lli getIdx(lli n){
        if (n <= sqN) return n - 1;
        else return  sz_vals - (N / n);
    }

    lli query(lli n) { return dp[getIdx(n)]; }

    void build(lli N) {
        for(auto n: poss_vals) 
        {
            dp[ getIdx(n)  ] = (powerSum(n) - 1 + MOD) % MOD ;
            dp2[ getIdx(n)  ] = (n - 1 + MOD) % MOD;
        }
            

        for(lli p = 2; p <= sqN; p++)
        {
            if(dp2[ getIdx(p) ] == dp2[ getIdx(p-1) ]) continue;
            lli p_k = binPower(p, k);

            primes.push_back(p);

            for(auto n: poss_vals) {
                if(p*p > n) break;

                if(n == N)
                {
                    ans_low += p * ((dp2[ getIdx(n / p)] - dp2[ getIdx(p-1) ]) + 1 + MOD) % MOD;
                    ans_low %= MOD;
                }

                dp[ getIdx(n) ] = (dp[ getIdx(n) ]  - (p_k*(dp[ getIdx(n / p)] - dp[ getIdx(p-1) ] + MOD) % MOD) + MOD)%MOD ; 
                dp2[ getIdx(n) ] = (dp2[ getIdx(n) ] - dp2[ getIdx(n / p)] + dp2[ getIdx(p-1) ] + MOD) % MOD;
            }
        }
    }
};



int main () {
	//fastIO();

    lli n; cin>>n;

    auto b = clock();

    SumPrimes *SP = new SumPrimes(n, 1);
    lli ans = ans_low + SP->query(n) - SP->query(primes.back()) + MOD;

    cout <<  ans % MOD << endl;

    cout << (double)(clock() - b) / CLOCKS_PER_SEC << endl;

	return 0;
}

