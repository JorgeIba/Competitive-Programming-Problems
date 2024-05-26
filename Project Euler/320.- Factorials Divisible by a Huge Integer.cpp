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

vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}

vector< pair<lli,int> > factorize(lli n){
    vector< pair<lli,int> > facts;

    while(n > 1){
        lli lp = lowestPrime[n];
        int power = 0;
        while( n % lp == 0 ){
            power++;
            n /= lp;
        }
        facts.push_back({lp, power});
    }
    return facts;
}


const lli MOD = 1e18;
int main () {
	fastIO();
	
    int N = 1'000'000;
    const lli EXP = 1'234'567'890;

    lowestPrimeSieve(N);

    auto legendre = [](lli n, int p = 2){
        lli sum = 0;
        while(n > 0){
            sum += n / p;
            n /= p;
        }
        return sum;
    };

    auto find_n = [&](lli p, lli target){
        lli l = 10, r = 1e18, ans = r;
        while(l <= r){
            lli mid = (l + r) / 2;
            if(legendre(mid, p) >= target){
                ans = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        return ans;
    };

    lli ans = 0;
    lli min_n = 0;
    for(int i = 10; i <= N; i++) {
        auto factors = factorize(i);

        lli max_n = 1;
        for(auto [p, k]: factors){
            auto ans_p = find_n(p, legendre(i, p) * EXP);
            max_n = max(max_n, ans_p);
        }
        min_n = max(min_n, max_n);

        ans += min_n;
        if(ans >= MOD) ans -= MOD;
    }
    cout << ans << endl;

	return 0;
}

