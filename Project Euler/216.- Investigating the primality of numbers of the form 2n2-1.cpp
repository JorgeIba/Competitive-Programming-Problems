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



lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


// Tonelli - Shanks
// Solve x^2 = a mod p
// If p*p > 1e18 use multMod
// Solutions = {x, p-x}
// O(lg^2 P)
lli sqrtMod(lli a, lli p) {
    if(p == 2) return a;
    if(a % p == 0) return 0;
    if( powerMod(a, (p-1)/2, p) == p-1 ) return -1;
    if(p % 4 == 3) return powerMod(a, (p+1)/4, p);

    lli S = 0, q = p-1;
    while(~q & 1) q>>=1, S++;

    lli n = 2;
    while(powerMod(n, (p-1)/2, p) != p-1) n++;

    lli M = S;
    lli c = powerMod(n, q, p);
    lli t = powerMod(a, q, p);
    lli R = powerMod(a, (q+1)/2, p);

    while(true) {
        if(t == 1) return R;

        lli aux_t = t;
        int m = 1;
        for(; m < M; m++) {
            aux_t = aux_t*aux_t % p;
            if(aux_t == 1) break;
        }
        lli b = powerMod(c, 1LL<<(M-m-1), p);
        // for(int i = 0; i < M-m-1; i++) b = b*b % p;
        M = m;
        c = b*b % p;
        t = t*c % p;
        R = R*b % p;
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


int main () {
	//fastIO();

    time_t begin = clock();

    lli N = 50*1e6;
    
    primesSieve(2*N+1);


    vector<lli> sieve(N+1), mark(N+1, 2);
    for(lli i = 2; i <= N; i++) sieve[i] = 2*i*i - 1;


    for(auto p: primes) {
        if( p == 2 ) continue;
        lli inv2 = powerMod(2, p-2, p);
        lli sol = sqrtMod(inv2, p);

        for(auto k: {sol, p-sol}) {
            for(lli idx = k; idx <= N; idx += p) {
                while(idx > 1 && mark[idx] > 0 && sieve[idx] % p == 0) {
                    mark[idx]--;
                    sieve[idx] /= p;
                }
            }
        }
    }


    lli ans = 0;
    for(int i = 2; i <= N; i++)
        ans += (mark[i] == 2 || (mark[i] == 1 && sieve[i] == 1)) ;


    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    cout << ans << endl;

	return 0;
}

