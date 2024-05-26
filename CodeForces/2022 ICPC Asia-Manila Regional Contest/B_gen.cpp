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


vector<bool> is_prime;
vector<int> sievePrimes(int n) {
    vector< int > primes;
    is_prime.resize(n+1, true);

    for(int i = 2; i <= n; i++){
        if(is_prime[i]) {
            primes.push_back(i);
            for(int j = 2*i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}


const int MAX_NP = 18000;
const int MOD = 1'169'996'969;
const int MAXN = 2000 + 10;
const int MAXP = 32;


#define uint unsigned int

uint ans[MAXN][MAXP][MAXP];

const int MAGIC_LIMIT = 450;

void generate_txt() {

    for(int j = 2; j < 30; j++){
        for(int k = j; k < 30; k++){
            vector< pair<int,int> > valids;
            for(int i = MAGIC_LIMIT; i <= 2000; i++) {
                if(is_prime[j] && is_prime[k] && ans[i][j][k]) {
                    valids.push_back({i, ans[i][j][k]});
                }
            }

            if(valids.empty()) continue; 

            cout << "f(" << j << "," << k << ",{";

            for(int i = 0; i < SZ(valids); i++){
                auto [n, ans] = valids[i];
                cout << n << "," << ans;
                if(i != SZ(valids)-1) cout << ",";
            }

            cout << "});";
        }
    }
}



int main () {
	fastIO();

    const int n = 2000;
    auto primes = sievePrimes(MAX_NP);

    primes.insert(primes.begin(), 0);
    auto sum_primes = primes;
    partial_sum(all(sum_primes), sum_primes.begin());


    vector<int> valid_primes;
    for(auto p: primes){
        if(p > 30) break;
        if(p != 0)
            valid_primes.push_back(p);
    }


    int total_sum = sum_primes.back();
    vector<uint> dp_old(total_sum+1);
    dp_old[0] = 1;


    for(int i = 1; i <= n; i++) {
        auto p = primes[i];

        int sum_upto = sum_primes[i];

        auto dp_new = dp_old;
        for(int sum = 0; sum <= sum_upto; sum++){
            if(sum - p >= 0) {
                dp_new[sum] += dp_old[sum-p];

                if(dp_new[sum] >= MOD) dp_new[sum] -= MOD;
            }                
        }

        for(auto p: valid_primes) {
            for(auto q: valid_primes){

                if(p == q) {
                    if(p != 2) continue;
                }

                int S_i = sum_primes[i];

                if((S_i * p) % (q + p) == 0) {
                    int x = (S_i * p) / (q + p);
                    ans[i][p][q] += dp_new[x];

                    if(ans[i][p][q] >= MOD) ans[i][p][q] -= MOD;
                }
                
            }
        }

        dp_old = dp_new;
    }

    
    generate_txt();


	return 0;
}

