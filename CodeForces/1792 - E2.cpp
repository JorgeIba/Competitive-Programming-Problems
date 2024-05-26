#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


vector< pair<lli,lli> > factorize(lli n){

    vector< pair<lli,lli> > primes;

    for(lli i = 2; i * i <= n; i++){
        if(n % i == 0) {
            int pot = 0;
            while(n % i == 0){
                pot++;
                n /= i;
            }
            primes.push_back({i, pot});
        }
    }

    if(n > 1) primes.push_back({n, 1});

    return primes;
}

vector<lli> divisors(lli n) {
    vector<lli> divs;
    for(lli i = 1; i * i <= n; i++){
        if(n % i == 0) {
            divs.push_back(i);
            if(i*i != n) divs.push_back(n / i);
        }
    }
    return divs;
}


typedef pair<lli,lli> pairi;

vector< pairi > facts;

lli power(lli a, lli b){
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a;
        b >>= 1;
        a = a * a;
    }
    return res;
}


map<lli,lli> dp;
lli f(lli d, int n){
    if(d <= n) return d;

    if(dp.count(d)) return dp[d];

    lli ans_d = 0;
    for(auto [p, e]: facts){
        if(d % p) continue;
        ans_d = max(ans_d, f(d / p, n));
    }
    return dp[d] = ans_d;
}


void main_(){
    lli n, m_1, m_2; cin>>n>>m_1>>m_2;

    dp.clear();

    auto facts_m_1 = factorize(m_1);
    auto facts_m_2 = factorize(m_2);

    map< lli, lli > facts_map(all(facts_m_1));
    for(auto [p, e]: facts_m_2) facts_map[p] += e;
    facts = vector<pair<lli,lli>>(all(facts_map));

    
    auto divs_m1 = divisors(m_1);
    auto divs_m2 = divisors(m_2);

    vector<lli> all_divs;
    for(auto d_1: divs_m1) 
        for(auto d_2: divs_m2)
            all_divs.push_back(d_1*d_2);

    sort(all(all_divs));

    all_divs.erase(unique(all(all_divs)), all_divs.end());

    lli ans_total = 0, ans_xor = 0;
    for(auto d: all_divs){

        auto ans_max_d = f(d, n);
        auto ans_min_d = d / ans_max_d;
        
        ans_total += (ans_min_d <= n);
        ans_xor ^= (ans_min_d <= n ? ans_min_d : 0);
    }
    cout << ans_total << " " << ans_xor << endl;
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

