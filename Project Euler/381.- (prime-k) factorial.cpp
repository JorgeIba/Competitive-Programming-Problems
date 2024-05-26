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


vector<int> sieve(int n){
    vector<bool> is_prime(n+1, true);
    vector<int> primes;
    for(int i = 2; i <= n; i++){
        if(is_prime[i]){
            primes.push_back(i);
            for(int j = 2*i; j <= n; j += i){
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

int powerMod(int a, int b, int mod){
    int res = 1;
    while(b){
        if(b&1) res = 1LL * res * a % mod;
        b >>= 1;
        a = 1LL * a * a % mod;
    }
    return res;
}


int main () {
	//fastIO();


    const int N = 1e8;
    const int K = 5;
    auto S = [&](int p){
        vector<lli> inv(K);
        forn(i, K) {
            inv[i] = powerMod(p-i-1, p-2, p);
        }

        int res = p-1, ans = 0;

        forn(i, K){
            ans += res;
            if( ans >= p ) ans -= p;

            res = 1LL * res * inv[i] % p;
        }
        return ans;
    };

    auto primes = sieve(N);

    lli sum = 0;
    for(auto p: primes) {
        if(p < 5) continue;

        sum += S(p);
    }

    cout << sum << endl;

	return 0;
}

