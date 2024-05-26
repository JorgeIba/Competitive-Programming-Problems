#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2")

#include<bits/stdc++.h>

#define lli long long int
#define ld long double

#define SZ(a) (int) a.size()
#define all(a) a.begin(), a.end()
#define endl "\n"

#define forn(i, n) for(int i = 0; i < n; i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


vector<int> muSieve(int n) {
    vector<int> Mu(n+1, -1);
    Mu[0] = 0, Mu[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(Mu[i]) {
            for(int j = 2*i; j <= n; j+= i) {
                Mu[j] -= Mu[i];
            }
        }
    }
    return Mu;
}

vector<int> sigmaSieve(int n){
    vector<int> sigma(n+1, 1);
    sigma[0] = 0, sigma[1] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            sigma[j]++;
        }
    }
    return sigma;
}


const int SQRT = 2e5;
const int MOD = 998244353;
const int THRESHOLD = 2e6; 

int main(){

    fastIO();

    auto mu = muSieve(THRESHOLD);
    auto g = sigmaSieve(THRESHOLD);

    vector<int> prefix_mu(THRESHOLD), prefix_sigma(THRESHOLD);
    for(int i = 1; i < THRESHOLD; i++)
        prefix_mu[i] = (prefix_mu[i-1] + abs(mu[i])) % MOD;

    for(int i = 1; i < THRESHOLD; i++)
        prefix_sigma[i] = (prefix_sigma[i-1] + abs(g[i])) % MOD;


    auto H = [&](lli n) {
        if(n < THRESHOLD) return prefix_mu[n];
        int sum = 0;
        for(lli i = 1; i*i <= n; i++) {
            int right = (n / (i*i)) % MOD;
            int left = mu[i];
            if(left < 0) left += MOD;

            sum += 1LL * left * right % MOD;
            if(sum >= MOD) sum -= MOD;
        }
        return sum;
    };

    auto G = [&](lli n) {
        if(n == 0) return 0;
        if(n < THRESHOLD) return prefix_sigma[n];

        int sum = 0;
        int m = sqrt(n);
        for(lli k = 1; k <= n/m; k++) {
            sum += (n/k) % MOD;
            if(sum >= MOD) sum -= MOD;
        }

        for(lli k = 1; k <= m-1; k++) {
            int left = (n /(k+1)) % MOD;
            int right = (n / k) % MOD;

            int range = right - left;
            if(range < 0) range += MOD;

            sum += 1LL * range * k % MOD;

            if(sum >= MOD) sum -= MOD;
        }
        return sum;
    };


    lli n; cin>>n;

    int sum = 0;
    lli m = sqrt(n);

    for(lli k = 1; k <= n/m; k++) {
        sum += 1LL * H(n/k) * g[k] % MOD;
        if(sum >= MOD) sum -= MOD;
    }

    for(lli k = 1; k <= m-1; k++) {
        int left = G(n/k) - G( n/(k+1) );
        if(left < 0) left += MOD;

        sum += 1LL * left * H(k) % MOD;
        if(sum >= MOD) sum -= MOD;
    }

    cout << sum << endl;

    return 0;
}
