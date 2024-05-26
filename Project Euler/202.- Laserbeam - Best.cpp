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

typedef vector<lli> VLL;
typedef vector<int> VI;


/*
    x + y = (N+3)/2
    gcd(x, y) == 1
    x = A + R
    y = A - 2*R
    x-y = A + R - (A - 2*R) =  3*R

    K = (N+3) / 2
    y = K - x
    gcd(x, y) = gcd(x, K-x) = gcd(x, K) = 1
    x-y = 0 mod 3  ->   x - (K - x) = 0 MOD

    Using mobius inversion:
    for(auto d: divs[k]){
        int sum = 0;
        for(int x = 1; x <= k; k++){
            if(x % 3 == 2 && x % d == 0)
                sum++;
        }
        ans += mu[d] * sum;
    }

    Using CRT
    for(auto d: divs[k]){
        auto [a, mod] = crt({2, 0}, {3, d});
        int sum = (K - a) / mod;
        ans += mu[d] * sum;
    }
*/

tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

pair<lli, lli> crt2(lli a_0, lli n_0, lli a_1, lli n_1){
    auto [d, s, t] = extendedGcd(n_0, -n_1);
    if((a_1 - a_0) % d) return {-1,-1};
    lli step = n_1 / d;
    lli k = s * (((a_1 - a_0) / d) % step) % step;
    if(k < 0) k += step;
    lli a = a_0 + n_0*k;
    lli mod = n_0 * step;
    return {a, mod};
}

vector<pair<lli,int>> getDivs(vector<lli> &factors){
    vector< pair<lli,int> > divs_mu;
    int n = SZ(factors);
    for(int mask = 0; mask < (1 << n); mask++){
        lli div = 1;
        int mu = 1;
        for(int j = 0; j < n; j++){
            if(mask & (1 << j)) {
                div *= factors[j];
                mu *= (-1);
            }
        }
        divs_mu.push_back({div, mu});
    }
    return divs_mu;
}

int main () {
	//fastIO();

    const lli N = 12'017'639'147;
    const lli K = 6008819575; // (N+3) / 2

    vector<lli> factors = {5, 11, 17, 23, 29, 41, 47};
    auto divs_mu = getDivs(factors);

    lli ans = 0;
    for(auto [d, mu_d]: divs_mu){
        auto [a, mod] = crt2(2*K % 3, 3, 0, d);
        lli sum = ((K - a) / mod + 1);
        
        if(a > K) continue;
        ans += mu_d * sum;
    }

    cout << ans << endl;

	return 0;
}

