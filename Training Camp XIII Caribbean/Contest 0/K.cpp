#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


int main () {
	//fastIO();

    lli n, k; cin>>n>>k;
    vector<lli> primes(k);
    for(auto &p: primes) cin>>p;

    lli ans = 0;
    for(int mask = 0; mask < (1LL << k); mask++){
        lli lcm = 1;
        for(int i = 0; i < k; i++) {
            if(mask & (1LL << i)){
                // if(lcm * primes[i] > n)
                if(lcm > n / primes[i]) lcm = n + 1;
                else lcm = lcm * primes[i];
            }
        }

        lli mult = (__builtin_popcount(mask) & 1 ? -1 : 1);

        ans += mult * (n / lcm);
    }

    cout << n - ans << endl;

	return 0;
}

