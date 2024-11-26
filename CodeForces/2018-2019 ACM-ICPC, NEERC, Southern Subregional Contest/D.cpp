#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

typedef unsigned long long ull;
inline ull multMod(ull a, ull b, ull c) {
    lli ret = a * b - c * ull(1.L / c * a * b);
    return ret + c * (ret < 0) - c * (ret >= (lli)c);
}


lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b) {
        if(b & 1) res = multMod(res, a, mod);
        b >>= 1;
        a = multMod(a, a, mod);
    }
    return res;
}

bool isPrime(lli n) {
    if(n < 2) return false;
    if(n <= 3) return true;
    if(~n & 1) return false;
    lli d = n - 1, s = 0;
    for(; (~d & 1); d >>= 1, s++);

    for(auto a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if(n == a) return true;
        auto res = powerMod(a, d, n);
        if(res == 1 || res == n-1)
            continue;

        lli x = s;
        while(--x) {
            res = multMod(res, res, n);
            if(res == n-1) break;
        }
        if(x == 0)
            return false;
    }
    return true;
}

lli getFactor(lli n) {
    lli a = rand(), b = rand();
    lli x = 2, y = 2, d = 1;
    auto f = [&](auto x) { return (multMod(x, x+a, n) + b) % n; };

    while(d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(abs(x-y), n);
    }
    return d;
}


map<lli,int> factors;
void factorizePollardRho(lli n, bool start = true) {
    if(start) 
        factors.clear();

    while(n > 1 && !isPrime(n)) {
        lli factor = n;
        while(factor == n)
            factor = getFactor(n);
        n /= factor;
        factorizePollardRho(factor, false);
        for(auto &[p, a]: factors) {
            while(n % p == 0) {
                n /= p;
                a++;
            }
        }
    }

    if(n > 1)
        factors[n]++;
}

vector<lli> getDivsByPrimes(vector< pair<lli,int> > &factors) {
    int n = SZ(factors);
    int factors_count = 1;
    for(int i = 0; i < n; i++) {
        factors_count *= (1 + factors[i].second);
    }
    vector<lli> divs(factors_count);
    divs[0] = 1;
    int count = 1;
    forn(stack_level, n) {
        int count_so_far = count;
        auto [p, a] = factors[stack_level];
        lli mult = 1;
        forn(j, a) {
            mult *= p;
            forn(i, count_so_far) {
                divs[count++] = divs[i] * mult;
            }
        }
    }
    return divs;
}


const int MAXN = 2e5 + 2;

int main () {
	// fastIO();

    auto get_divs = [&](lli x) {
        factorizePollardRho(x);
        vector< pair<lli,int> > facts(all(factors));
        return getDivsByPrimes(facts);
    };

    int n; cin>>n;
    vector< pair<int,int> > nums(n);
    vector<int> original(n);
    vector<int> ans(n);
    forn(i, n) {
        int x; cin>>x;
        original[i] = x;
        nums[i] = {x, i};
    }
    sort(all(nums));


    vector<lli> divs;
    int bef = -1;
    int j = 0;
    forn(i, n) {
        auto [x, idx] = nums[i];
        if(bef != x) {
            divs = get_divs(x);
            j = 0;
        }

        if(j == SZ(divs)) {
            cout << "NO" << endl;
            return 0;
        }

        ans[idx] = divs[j++];

        bef = x;
    }

    cout << "YES" << endl;
    forn(i, n) {
        cout << ans[i] << " " << original[i] / ans[i] << endl;
    }


	return 0;
}

