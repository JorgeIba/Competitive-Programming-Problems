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

const int maxN = 1e6+5, MOD = 1e7+7, inv2 = 5e6 + 4;

lli Gauss(lli n)
{
    n %= MOD;
    return n*(n+1)%MOD * inv2 % MOD;
}

void solve(lli n)
{
    lli ans = 1;

    for(auto p: primes)
    {
        if(p > n) break;
        lli sum = 0, act = p;
        while(act <= n)
        {
            sum += n/act;
            act*=p;
        }
        ans = ans*Gauss(sum+1)%MOD;
    }

    cout << ans << endl;
}


int main () {
	fastIO();
    primesSieve(maxN);

    lli n;
    while(cin>>n)
    {
        if(!n) break;
        solve(n);
    } 
    
	return 0;
}