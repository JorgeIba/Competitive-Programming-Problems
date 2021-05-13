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
vector<int> primes;
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

/*

lli f(lli n, lli idx)
{
    if(n == 0)
    {
        return 1;
    }
    else if(n < 0) return 0;

    if(primes[idx] > n) return 0;

    if(dp[n][idx] != -1) return dp[n][idx];

    lli tomar = f(n-primes[idx], idx);
    lli no_tomar = f(n, idx+1);
    
    return dp[n][idx] = tomar + no_tomar;
}
*/

const lli upper = 5*1e3;
lli dp[upper][upper];

int main () {
	//fastIO();
    primesSieve(1000);
    
    dp[0][0] = 1;
    for(int n = 0; n < 100; n++)
    {
        for(int idx = 0; idx < SZ(primes); idx++)
        {
            lli prime = primes[idx];
            if(n + prime <= upper)
            {
                dp[n + prime][idx] += dp[n][idx];
            }
            dp[n][idx+1] += dp[n][idx];
            if(dp[n][idx] >= upper)
            {
                cout << n << endl;
                return 0;
            }
        }
    }
    
	return 0;
}