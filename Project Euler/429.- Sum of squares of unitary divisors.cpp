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
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


lli binPow(lli a, lli b, lli mod){
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a*a % mod;
    }
    return res;
}


const lli maxN = 1e8;
const lli MOD = 1e9+9;
int main () {
	//fastIO();

    time_t start = clock();
    lli n = maxN;

    primesSieve(maxN);

    vector<pair<lli,lli>> factors;

    for(auto p: primes) {
        lli cnt = 0;
        lli aux = n;
        while(aux > 0) {
            cnt += (aux / p);
            aux /= p;
        }
        factors.push_back({p, cnt});
    }

    lli ans = 1;
    for(auto [p, e]: factors) {
        ans = ans * (1 + binPow(p, 2*e, MOD)) % MOD;
    }

    cout << ans << endl;

    cout << (ld)(clock() - start)/CLOCKS_PER_SEC << endl;

	return 0;
}

