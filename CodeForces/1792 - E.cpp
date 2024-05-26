#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace __gnu_pbds;


using namespace std;


vector< pair<int,int> > factorize(int n){

    vector< pair<int,int> > primes;

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

vector<int> divisors(lli n) {
    vector<int> divs;
    for(lli i = 1; i * i <= n; i++){
        if(n % i == 0) {
            divs.push_back(i);
            if(i*i != n) divs.push_back(n / i);
        }
    }
    return divs;
}


typedef pair<int,int> pairi;

vector< pairi > facts;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct custom_hash {
    int operator()(int x) const { return x ^ RANDOM; }
};

gp_hash_table<lli, lli, custom_hash> dp; // va a madres
lli f(lli d, int n){
    if(d <= n) return d;

    if(dp[d]) return dp[d];

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

    map< int, int > facts_map(all(facts_m_1));
    for(auto [p, e]: facts_m_2) facts_map[p] += e;
    facts = vector<pair<int,int>>(all(facts_map));

    
    auto divs_m1 = divisors(m_1);
    auto divs_m2 = divisors(m_2);


    set<lli> check;
    lli ans_total = 0, ans_xor = 0;
    for(auto d_1: divs_m1) {
        for(auto d_2: divs_m2) {
            auto d = 1LL*d_1*d_2;

            if(check.count(d)) continue;

            auto ans_max_d = f(d, n);
            auto ans_min_d = d / ans_max_d;
            
            ans_total += (ans_min_d <= n);
            ans_xor ^= (ans_min_d <= n ? ans_min_d : 0);

            check.insert(d);
        }
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