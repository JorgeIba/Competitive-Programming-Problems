#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ull unsigned long long
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


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
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


lli powerMod(lli a, lli b, lli mod){
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



int main () {
	//fastIO();

    time_t begin = clock();


    const lli MOD = 1e18;
    lli N = 1e7;

    primesSieve(2*N);
    vector< lli > f(N+1);
    for(lli i = 1; i <= N; i++) f[i] = 4 * i * i + 1;
    
    vector<lli> grFactor(N+1);

    for(auto p: primes) {
        if(p == 2) continue;

        lli inv2 = powerMod(4, p-2, p);
        lli sol = sqrtMod((p-1)*inv2 % p, p);

        if(sol == -1 || sol == 0) continue;

        for(auto k: {sol, p-sol}){
            
            for(lli i = k; i <= N; i += p) {
                grFactor[i] = max(grFactor[i], p);

                while(f[i] % p == 0){
                    
                    f[i] /= p;
                };
            }
            
        }
        
    }


    lli ans = 0;
    for(int i = 1; i <= N; i++) {
        ans = (ans + max(grFactor[i], f[i])) % MOD;
    }

    cout << (double) (clock() - begin) / CLOCKS_PER_SEC << endl;
    cout << ans << endl;

	return 0;
}

