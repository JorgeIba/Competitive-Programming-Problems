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


unordered_map<lli,lli> dp_G;
lli G(lli n) {
    if(dp_G.count(n)) return dp_G[n];
    lli sum = 0, limit = sqrt(n);
    for(lli i = 1; i <= limit; i++) {
        sum += n/i;
    }
    return dp_G[n] = 2*sum - limit*limit;
}

lli h(lli p, lli a){
    if(a == 0) return 0;
    return (1LL << (a-2));
}


// Calculates prefix sum of f(n) where f(n) = h o g
// G(n) is easy to calculate and h(p) = 0
// Works in O(sqrt(n))
lli f(lli n, lli curr_h, int idx_prime=-1) {
    lli ans = G(n) * curr_h;

    for(int idx_next = idx_prime+1; idx_next < SZ(primes); idx_next++){
        lli p = primes[idx_next];
        lli curr_n = n / (p*p);
        if(curr_n == 0) break;
        int exp = 2;

        while (curr_n > 0){
            ans += f(curr_n, curr_h * h(p, exp), idx_next);
            curr_n /= p;
            exp++;
        }
    }
    return ans;
}



int main () {
	//fastIO();
	lli N; cin>>N;

    time_t start = clock();

    primesSieve(sqrt(N)+1);

    cout << f(N, 1) << endl;
    cout << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

	return 0;
}

