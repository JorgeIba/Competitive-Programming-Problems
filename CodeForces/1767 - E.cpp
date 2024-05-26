#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const lli INF = 1e9;


int main () {
	//fastIO();
    int n, m; cin>>n>>m;

    vector<lli> colors(n);
    for(auto &x: colors){
        cin>>x; x--;
    }

    vector<lli> costs(m);
    for(auto &x: costs) cin>>x;

    int first_half = m/2;
    int second_half = m - first_half;


    vector< lli > mat(m);

    for(int i = 0; i < n-1; i++){
        auto c_i = colors[i], c_j = colors[i+1];
        mat[c_i] |= (1LL << c_j);
        mat[c_j] |= (1LL << c_i);
    }

    mat[ colors[0] ] |= (1LL << colors[0]);
    mat[ colors[n-1] ] |= (1LL << colors[n-1]);

    auto mask_contains = [&](lli mask, int idx) {
        return mask & (1ll << idx);
    };

    auto get_cost_first = [&](lli mask) {
        lli sum = 0;
        for(int i = 0; i < first_half; i++)
            if(mask_contains(mask, i))
                sum += costs[i];
        return sum;
    };

    auto get_cost_second = [&](lli mask) {
        lli sum = 0;
        for(int i = 0; i < second_half; i++)
            if(mask_contains(mask, i))
                sum += costs[i + first_half];
        return sum;
    };

    vector< lli > total_costs_first(1LL << first_half, INF);
    for(int mask = 0; mask < (1LL << first_half); mask++){
        
        lli must_be = 0;
        for(int i = 0; i < first_half; i++)
            if(!mask_contains(mask, i))
                must_be |= mat[i];

        must_be &= (1LL << first_half) - 1;

        if((must_be & mask) == must_be) {
            total_costs_first[mask] = get_cost_first(mask);
        }
    }


    vector<lli> dp(1LL << first_half, INF);
    for(int mask = 0; mask < (1ll << first_half); mask++){
        dp[mask] = min(dp[mask], (total_costs_first[mask] != INF ? 0 : INF));
        for(int i = 0; i < first_half; i++){
            if(!mask_contains(mask, i)) {
                dp[mask ^ (1ll << i)] = min(dp[mask ^ (1ll << i)], dp[mask]);
            }
        }
    }


    for(int mask = (1ll << first_half) - 1; mask >= 0; mask--){
        for(int i = 0; i < first_half; i++) {
            if(mask_contains(mask, i)){
                dp[mask ^ (1ll << i)] = min(dp[mask ^ (1ll << i)], dp[mask] + costs[i]);
            }
        }
    }



    vector<lli> total_costs_second(1LL << second_half, INF);
    for(int mask = 0; mask < (1LL << second_half); mask++){

        lli must_be = 0;
        
        for(int i = 0; i < second_half; i++)
            if(!mask_contains(mask, i))
                must_be |= mat[i + first_half];

        must_be >>= first_half;
        must_be &= (1LL << second_half) - 1;

        if((must_be & mask) == must_be) {
            total_costs_second[mask] = get_cost_second(mask);
        }
    }


    lli ans = INF;
    for(int mask = 0; mask < (1ll << second_half); mask++) {
        if(total_costs_second[mask] == INF) continue;

        lli mask_must = 0;
        for(int i = 0; i < second_half; i++) {
            if(!mask_contains(mask, i))
                mask_must |= (mat[i+first_half] & ((1ll << first_half) -1));
        }

        // cout << "mask: ";
        // print_mask(mask); cout << endl; 

        // cout << "mask_must: ";
        // print_mask(mask_must); cout << endl;

        ans = min(ans, total_costs_second[mask]  + dp[mask_must] + get_cost_first(mask_must));
    }

    cout << ans << endl;
    




	return 0;
}

