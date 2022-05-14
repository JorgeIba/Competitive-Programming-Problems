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


lli multMod(lli a, lli b, lli mod) {
    lli res = 0;
    while(b) {
        if(b&1) res = (res + a) % mod;
        b >>= 1;
        a = (a+a) % mod;
    }
    return res;
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a*a % mod;
    }
    return res;
}

lli power(lli a, lli b) {
    lli res = 1;
    while(b) {
        if(b&1) res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}




tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

lli modularInverse(lli a, lli m){
	auto[d, x, y] = extendedGcd(a, m);
	if(d != 1) return -1; // inverse doesn't exist
	if(x < 0) x += m;
	return x;
}

// Tonelli - Shanks
// Solve x^2 = a mod p
// If p*p > 1e18 use multMod
// Solutions = {x, p-x}
// O(lg^2 P)
lli sqrtMod(lli a, lli p) {
    a %= p;
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



// Solve x^2 = n  mod p^k
// p is odd prime
// Solutions: {x, p^k - x};
lli sqrtModK(lli n, lli p, lli k) {
    // Initial value
    lli ans_i = sqrtMod(n, p); 
    if(ans_i == -1 || ans_i == 0) return ans_i;

    lli reps = 0;
    while((1LL << reps) < k) reps++;
    lli pi = p;

    for(int i = 1; i <= reps; i++) {
        // f(ans + p^i * t ) = 0 mod p^2i

        lli inv = modularInverse(2*ans_i, pi);
        lli c = (n-ans_i*ans_i)/pi;
        lli t = c * inv % pi;
        if(t < 0) t+= pi;

        ans_i = ans_i + pi*t;
        pi = pi * pi;

        ans_i %= pi;
    }

    lli pk = power(p, k);
    return ans_i % pk;
}






int main () {
	// fastIO();

    time_t begin = clock();

    const lli N = 1e7;

    primesSieve(N);

    lli ans = 0;
    for(auto p: primes) {
        lli p2 = p*p;
        lli sol_1 = sqrtModK(13, p, 2), sol_2 = p2 - sol_1;

        if(p == 2 || p == 13 || sol_1 == -1) continue;

        lli inv = modularInverse(2, p2);

        
        lli n_1 = multMod(sol_1 + 3, inv, p2);
        lli n_2 = multMod(sol_2 + 3, inv, p2);

        lli ans_p = min(n_1, n_2);
        
        ans += ans_p;
    }

    cout << "Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    cout << ans << endl;

	return 0;
}

