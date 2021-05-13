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

lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


lli get_number(lli p1, lli p2)
{
    lli sz_p1 = SZ( to_string(p1)  );
    lli x = binPow(10, sz_p1, p2);
    lli new_val = p2 - p1;

    lli left_val = new_val * binPow(x, p2-2, p2) % p2;


    lli ans = pow(10, sz_p1) * left_val + p1;

    assert(ans % p2 == 0);
    return ans;
}


lli limitP1 = 1e6;
lli limitN = limitP1+100;


int main () {
	fastIO();

    primesSieve(limitN);

    lli ans = 0;
    for(int i = 2, p1 = primes[i], p2 = primes[i+1]; p1<=limitP1; i++, p1 = primes[i], p2 = primes[i+1])
    {
        ans += get_number(p1, p2);
    }
    cout << ans << endl;

	return 0;
}