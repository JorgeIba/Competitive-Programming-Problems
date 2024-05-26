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


typedef int64_t ll;
typedef uint64_t ull;

inline ull multMod(ull a, ull b, ull c) {
  ll ret = a * b - c * ull(1.L / c * a * b);
  return ret + c * (ret < 0) - c * (ret >= (ll)c);
}

inline lli powerMod(lli a, lli b, lli mod) {
    lli res = 1; 
    while(b) {
        if(b & 1) res = multMod(res, a, mod);
        b >>= 1;
        a = multMod(a, a, mod);
    }
    return res;
}


//22
bool isPrimeMillerRabin(lli n)
{
    if(n < 2) return false;
    if(n <= 3) return true;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d>>=1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if(n == a) return true;
        lli residuo = powerMod(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x)
        {
            residuo = multMod(residuo, residuo, n);
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}




// lli getFactor(lli n) {
//     lli a = rand(), b = rand();
//     lli x = 2, y = 2, d = 1;

//     auto f = [&](auto x){ return (multMod(x, x+a, n) + b) % n; };

//     while(d == 1) {
//         x = f(x);
//         y = f(f(y));
//         d = __gcd(abs(x-y), n);
//     }

//     return d;
// }

lli getFactor(lli n){
    lli a = rand(), b = rand();
    lli x = 2;

    auto f = [&](auto x){ 
        lli aux = multMod(x, x+a, n) + b;
        return aux >= n ? aux - n : aux;
    };

    for(int l = 256; l < (1 << 20); l <<= 1) {
        lli y = x;
        for(int i = 0; i < l; i++){
            x = f(x);
            if(lli g = gcd(abs(x-y), n); g != 1) {
                return g;
            }
        }
    }
    return 1;
}


map<lli,int> factors;
void factorizePollardRho(lli n, lli start = true) {
    if(start) factors.clear();
    if(n == 1) return;

    if(isPrimeMillerRabin(n)) {
        factors[n]++;
        return;
    }

    lli factor = n;
    while(factor == n) factor = getFactor(n);


    factorizePollardRho(factor, false);
    factorizePollardRho(n/factor, false);
}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) {
        lli n; cin>>n;

        factorizePollardRho(n);

        vector<lli> ans;
        for(auto [p, a]: factors) {
            for(int i = 0; i < a; i++) {
                ans.push_back(p);
            }
        }
        cout << SZ(ans) << " ";
        for(auto x: ans) cout << x << " ";
        cout << endl;
    }

	return 0;
}

