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


pair<lli,lli> get_children(lli n){

    int level = __lg(n);
    lli l, r;

    // Left is complete
    if(n & (1LL << (level-1))){
        l = (1LL << level) - 1;
    } else {
        l = (1LL << (level-1)) - 1 + (n - (1LL << level) + 1);
    }

    r = n - 1 - l;

    return {l, r};
}


const int MAX_CHAIN = 61;
const int MAX_DIST = 2*MAX_CHAIN;
const int MOD = 998244353;

map< lli, pair<vector<int>, vector<int>> > dp;

pair< vector<int>, vector<int> > f(lli n){
    if(n == 0){
        vector<int> all_ways(MAX_DIST);
        vector<int> all_chain(MAX_CHAIN); 
        return {all_ways, all_chain};
    }
    if(n == 1){
        vector<int> all_ways(MAX_DIST); all_ways[1] = 1;
        vector<int> all_chain(MAX_CHAIN); all_chain[0] = 1;
        return {all_ways, all_chain};
    }

    if(dp.count(n)) return dp[n];

    auto [l, r] = get_children(n);

    auto [ways_l, chain_l] = f(l);
    auto [ways_r, chain_r] = f(r);


    vector<int> all_ways(MAX_DIST);
    for(int i = 0; i < MAX_DIST; i++) {
        all_ways[i] = (ways_l[i] + ways_r[i]);
        if(all_ways[i] >= MOD) all_ways[i] -= MOD;
    }

    rotate(chain_l.begin(), chain_l.begin() + chain_l.size() - 1, chain_l.end());
    rotate(chain_r.begin(), chain_r.begin() + chain_r.size() - 1, chain_r.end());
    
    vector<int> all_chains(MAX_CHAIN);
    for(int i = 0; i < MAX_CHAIN; i++){
        all_chains[i] = (chain_l[i] + chain_r[i]); 
        if(all_chains[i] >= MOD) all_chains[i] -= MOD;
    }
    all_chains[0] = 1;

    chain_l[0] = 1;
    chain_r[0] = 1;

    for(int i = 0; i < MAX_CHAIN; i++){
        for(int j = 0; j < MAX_CHAIN; j++){
            all_ways[i + j + 1] += 1LL * chain_l[i] * chain_r[j] % MOD;
            if(all_ways[i + j + 1] >= MOD) all_ways[i + j + 1] -= MOD;
        }
    }

    return dp[n] = {all_ways, all_chains};
}


lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

void main_(){
    lli n, m; cin>>n>>m;

    int ans = 0;
    auto [ways, _] = f(n);

    int inv_m = powerMod(m, MOD-2);

    for(int l = 0; l < MAX_DIST; l++) {
        int sum = 0;
        for(int p = 1; p <= m; p++){
            lli aux = powerMod(p, l) - powerMod(p-1, l);
            if(aux < 0) aux += MOD;

            sum += 1LL * p * aux % MOD;
            if(sum >= MOD) sum -= MOD;
        }

        ans += 1LL * ways[l] * powerMod(inv_m, l) % MOD * sum % MOD;
        if(ans >= MOD) ans -= MOD;
    }
    cout << ans * powerMod(m, n) % MOD << endl;
}


int main () {
	fastIO();

	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

