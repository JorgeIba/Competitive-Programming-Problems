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

const lli MOD = 1e9+7;

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

lli binPow(lli a, lli b){
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a %MOD;
        b>>=1;
        a = a*a %MOD;
    }
    return res;
}


int main () {
	fastIO();

    primesSieve(1.5*1e6);

    lli n, q; cin>>n>>q;
    vector<lli> A(n), B(n);
    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;

    vector<lli> prefix_A(n), prefix_B(n);
    for(int i = 0; i<n; i++)
    {
        prefix_A[i] = (i?prefix_A[i-1]:1) * primes[ A[i] ] % MOD;
        prefix_B[i] = (i?prefix_B[i-1]:1) * primes[ B[i] ] % MOD;
    }

    while(q--)
    {
        lli x, y, r; cin>>x>>y>>r;
        x--, y--;


        lli l_A = (x? prefix_A[x-1] : 1);
        lli r_A = prefix_A[x+r-1];
        lli hash_A = r_A * binPow(l_A, MOD-2) % MOD;

        lli l_B = (y? prefix_B[y-1] : 1);
        lli r_B = prefix_B[y+r-1];
        lli hash_B = r_B * binPow(l_B, MOD-2) % MOD;

        //cout << l_A << " " << r_A << " " << l_B << " " << r_B << " " << hash_A << " " << hash_B << " ";
        if(hash_A == hash_B) cout << "YES\n";
        else cout << "NO\n";
    }

    
	return 0;
}