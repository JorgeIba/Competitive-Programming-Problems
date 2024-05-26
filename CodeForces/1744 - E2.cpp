// Problem: E2. Divisible Numbers (hard version)
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/E2
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define ull unsigned long long

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

// L < k*num <= R
lli sol(lli L, lli R, lli num) {
	lli L_aux = L/num, R_aux = R/num;
	
	for(lli k = L_aux; k <= R_aux; k++) {
		if( L < k*num && k*num <= R) {
			return k*num;
		}
	} 
	return -1;
}


ull multMod(ull a, ull b, ull mod) {
    ull res = 0;
    a %= mod;
    while(b) {
        if(b & 1){
            res += a;
            res = res >= mod ? res - mod : res;
        };
        b >>= 1;
        a <<= 1;
        a = a >= mod ? a - mod : a;
    }
    return res;
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


lli getFactor(lli n) {
    lli a = rand(), b = rand();
    lli x = 2, y = 2, d = 1;

    auto f = [&](auto x){ return (multMod(x, x+a, n) + b) % n; };

    while(d == 1) {
        x = f(x);
        y = f(f(y));
        d = __gcd(abs(x-y), n);
    }

    return d;
}


map<lli,int> factors;
void factorizePollardRho(lli n, lli start = true) {
    if(start) factors.clear();
    
    // You can reduce by trial division [2, 3, 5, 7, ...]

    while(n > 1 && !isPrimeMillerRabin(n)) {
        lli factor = n;
        while(factor == n) factor = getFactor(n);
        n /= factor;
        factorizePollardRho(factor, false);
        for(auto &[p, a]: factors) {
            while(n % p == 0) {
                n /= p;
                a++;
            }
        }
    }
    
    if(n > 1) factors[n]++;
}


vector<lli> getDivs(const vector<pair<lli,lli>> &factors)
{
    int n = SZ(factors);
    int factors_count = 1;
    for (int i = 0; i < n; ++i)
    {
        factors_count *= 1+factors[i].second;
    }
    vector<lli> divs(factors_count); divs[0] = 1;
    int count = 1;
    for (int stack_level = 0; stack_level < n; ++stack_level)
    {
        int count_so_far = count;
        int prime = factors[stack_level].first;
        int exponent = factors[stack_level].second;
        int multiplier = 1;
        for (int j = 0; j < exponent; ++j)
        {
            multiplier *= prime;
            for (int i = 0; i < count_so_far; ++i)
            {
                divs[count++] = divs[i] * multiplier;
            }
        }
    }
    return divs;
}



void solve(){
	lli a, b, c, d; cin>>a>>b>>c>>d;

	lli Lx = a, Rx = c;
	lli Ly = b, Ry = d;
	
	
	factorizePollardRho(a*b);
	vector<pair<lli,lli>> facts;
	for(auto [p, a]: factors) facts.push_back({p, a});
	
	
	vector<lli> divs = getDivs(facts);
	
	for(auto d: divs){
		lli num_x = d, num_y = (a*b) / d;
		lli x = sol(Lx, Rx, num_x);
		lli y = sol(Ly, Ry, num_y);
		
		if(x != -1 && y != -1) {
			cout << x << " " << y << endl;
			return;
		}
	}
	
	cout << -1 << " " << -1 << endl;
}


int main () {
	//fastIO();

	lli t; cin>>t;
	
	while(t--) solve();



	return 0;
}

