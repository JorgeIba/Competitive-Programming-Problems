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
    lli N = 5e15;
    lli M = sqrt(N);
    cout << M << endl;
    primesSieve(M+10);


    auto f = [&](lli n) {
        return n*n + (n+1)*(n+1);
    };

    vector<lli> sieve(M+1), mark(M+1, 2);
    for(lli i = 0; i <= M; i++) sieve[i] = f(i);



    for(auto p: primes) {
        if(p == 2) continue;
        lli val = p + (-4)%p;
        
        lli sol = sqrtMod(val, p);
        if(sol == -1) continue;

        for(auto k: {sol, p-sol}) {
            lli x = (k-2+p) * powerMod(4, p-2, p) % p;

            for(lli idx = x; idx <= M; idx += p) {
                while(idx > 0 && mark[idx] > 0 && sieve[idx] % p == 0) {
                    mark[idx]--;
                    sieve[idx] /= p;
                }
            }
        }
    } 

    


    lli sum = 0;
    for(lli i = 1; i <= M; i++) {
        lli fi = f(i);
        if(fi >= N) break;
        if(mark[i] == 2 || (mark[i] == 1 && sieve[i] == 1)) {
            // cerr << fi << endl;
            sum++;
        }
    }

    cout << sum << endl;


	return 0;
}

