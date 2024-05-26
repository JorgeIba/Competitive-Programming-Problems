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


tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}


pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extendedGcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}

lli inverse(lli a, lli m){
	auto[d, x, y] = extendedGcd(a, m);
	if(d != 1) return -1;
	if(x < 0) x += m;
	return x;
}

struct BinomialPrimePower{
    lli p, k;
    lli pk;
    vector<lli> fact_p;
    vector<lli> powers_p;

    BinomialPrimePower() {}
    BinomialPrimePower(lli p, lli k): p(p), k(k){
        pk = pow(p, k);
        fact_p.resize(pk, 1); 

        for(int i = 2; i < pk; ++i){
            if(i % p == 0) 
                fact_p[i] = fact_p[i-1];
            else
                fact_p[i] = 1LL*i*fact_p[i-1] % pk;
        }

        int max_alpha = 65; // Maximum exponent of p in n
        powers_p.resize(max_alpha, 1);
        for(int i = 1; i < max_alpha; i++){
            powers_p[i] = 1LL * p * powers_p[i-1] % pk;
        }
    }

    // n! = a x p^k where gcd(n!,a) = 1
    // returns [a % pk, k]
    pair<lli,lli> fact_n(lli n){
        if(n == 0 || n == 1) return {1, 0};

        lli fact_pk;
        if(p > 2 || pk == 4){ // fact_pk = pk-1;
            if(n/pk % 2 == 0)
                fact_pk = 1;
            else
                fact_pk = pk-1;
        }
        else {
            fact_pk = 1;
        }

        lli alpha_1 = n / p;
        lli a_1 = fact_pk * fact_p[n % pk] % pk;

        auto [a_2, alpha_2] = fact_n( n / p );
        return {a_1 * a_2 % pk, alpha_1 + alpha_2};
    }

    lli nCr(lli n, lli r){
        if(n < 0 || r < 0 || r > n) return 0;

        auto [a_n, alpha_n] = fact_n(n);
        auto [a_r, alpha_r] = fact_n(r);
        auto [a_nr, alpha_nr] = fact_n(n - r);

        int power = alpha_n - alpha_r - alpha_nr;
        if(power >= k) return 0;
    
        return a_n * inverse(a_r, pk) % pk * inverse(a_nr, pk) % pk * powers_p[power] % pk;
    }
};




vector< pair<int,int> > factorize(int n){
    vector<pair<int,int>> facts;

    for(int i = 2; 1LL * i * i <= n; i++) {
        if(n % i == 0) {
            int power = 0;
            while(n % i == 0){
                n /= i;
                power++;
            }
            facts.push_back({i, power});
        }
    }
    if(n > 1) facts.push_back({n, 1});
    return facts;
}




int main () {
	fastIO();

    int t, m; cin>>t>>m;

    auto facts = factorize(m);
    int r = SZ(facts);

    vector< BinomialPrimePower > BPPs(r);
    forn(i, r){
        auto [p, e] = facts[i];
        BPPs[i] = BinomialPrimePower(p, e);
    }

    while(t--){
        lli n, k; cin>>n>>k;
        if(m == 1){
            cout << 0 << endl;
            continue;
        }

        vector<lli> a(r), mods(r);

        forn(i, r){
            a[i] = BPPs[i].nCr(n, k);
            mods[i] = BPPs[i].pk;
        }

        auto [ans, mod] = crt(a, mods);
        assert(mod == m);
        cout << ans << endl;
    }


	return 0;
}

