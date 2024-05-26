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


#define i128 __int128


i128 powerMod(i128 a, i128 b, i128 mod){
    i128 res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


//22
bool isPrimeMillerRabin(lli n)
{
    if(n < 2) return false;
    if(n <= 3) return true;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d>>=1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if(n == a) return true;
        i128 residuo = powerMod(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x)
        {
            residuo = residuo * residuo % (i128) n;
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
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


vector<lli> quadratic_sieve(vector<lli> sieve, lli add) {
    vector<lli> sieve_prime = sieve, mark(SZ(sieve), 1);

    for(auto p: primes) {
        // f(x) = x*x + add
        // x*x = p-add mod p
        lli sol = sqrtMod(p-(add%p), p);
        if(sol == -1) continue;

        for(auto k: {sol, p-sol}) {
            for(int idx = k; idx < SZ(sieve); idx += p ) {

                while(mark[idx] >= 0 && sieve[idx] % p == 0) {
                    mark[idx]--;
                    sieve_prime[idx] = p;
                    sieve[idx] /= p;
                }
            }
        }
    }

    for(int i = 0; i < SZ(sieve); i++) {
        if(!(mark[i] == 0 || mark[i] == 1)) sieve_prime[i] = -1;
    }
    return sieve_prime;
}

vector<lli> add = { 1, 3, 7, 9, 13, 27 };



int main () {
	// fastIO();

    time_t begin = clock();

    lli N = 150*1e6;
    primesSieve(N + 100);

    vector< vector<lli> > fx(6, vector<lli>(N+1));

    for(int i = 0; i < 6; i++) {
        for(lli j = 0; j <= N; j++) {
            fx[i][j] = j*j + add[i];
        }
    }

    for(int i = 0; i < 6; i++) {
        fx[i] = quadratic_sieve(fx[i], add[i]);
    }


    map<lli,lli> index_primes;
    for(int i = 0; i < SZ(primes); i++) index_primes[primes[i]] = i+1;
    

    auto areConsecutive = [&](lli p1, lli p2) {
        if(p1 == -1 || p2 == -1) return false;
        if(p2 <= p1) return false;

        if(index_primes.count(p1) && index_primes.count(p2))   
            return index_primes[p2] == index_primes[p1] + 1;


        for(lli val = p1 + 1; val < p2; val++) {
            if(isPrimeMillerRabin(val))
                return false;
        }

        return true;
    };


    lli sum = 0;
    for(int i = 0; i < N; i++) {

        if(fx[0][i] != -1) {
            bool is_valid = true;
            for(int j = 1; j < 6; j++) {
                if(!areConsecutive(fx[j-1][i], fx[j][i])) {
                    is_valid = false;
                    break;
                }       
            }

            if(is_valid){
                cout << i << endl;
            }

            sum += (is_valid ? i : 0);
        }
    }    

    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    cout << sum << endl;

	return 0;
}

