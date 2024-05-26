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


const int MAXM = 60;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli random(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}

int main () {
	//fastIO();
	
    int n, m, p; cin>>n>>m>>p;
    int threshold = (n+1)/2;

    vector< lli > masks(n);

    forn(i, n){
        string s; cin>>s;
        bitset<MAXM> aux(s);
        masks[i] = aux.to_ullong();
    }


    auto print_mask = [](lli mask){
        return bitset<MAXM>(mask).to_string();
    };


    auto get_max = [](int ans_cnt, lli ans_mask, int poss_cnt, lli poss_mask) -> pair<int,lli> {
        if(ans_cnt < poss_cnt){
            return {poss_cnt, poss_mask};
        } 
        return {ans_cnt, ans_mask};
    };

    

    int ans_total = 0;
    lli ans_mask_total = 0;

    const int MAX_ITER = 80;
    forn(iter, MAX_ITER) {

        int idx_fix = random(0, n-1); 

        lli mask_fixed = masks[idx_fix];

        vector<int> masks_p(n);

        int cnt_i = 0;
        for(int i = 0; i < MAXM; i++){
            if(mask_fixed & (1LL << i)){

                for(int j = 0; j < n; j++){
                    if(masks[j] & (1LL << i)){
                        masks_p[j] |= (1 << cnt_i);
                    }
                }

                cnt_i++;
            }
        }

        vector<int> likes(1 << cnt_i);
        vector<int> fr(1 << cnt_i);

        for(int i = 0; i < n; i++){
            fr[masks_p[i]]++;
        }

        for(int mask = 0; mask < (1 << cnt_i); mask++){
            for(int submask = mask; submask; submask=(submask-1) & mask) {
                likes[submask] += fr[mask];
            }
        }

        int ans_cnt = 0, ans_mask = 0;
        for(int mask = 0; mask < (1 << cnt_i); mask++){
            if(likes[mask] >= threshold) {
                int cnt = __builtin_popcount(mask);
                tie(ans_cnt, ans_mask) = get_max(ans_cnt, ans_mask, cnt, mask);
            }
        }


        if(ans_cnt == 0) continue;

        lli good_mask = 0;
        cnt_i = 0;
        for(int i = 0; i < MAXM; i++){
            if(mask_fixed & (1LL << i)){
                if(ans_mask & (1 << cnt_i)){
                    good_mask |= (1LL << i);
                }
                cnt_i++;
            }
        }

        tie(ans_total, ans_mask_total) = get_max(ans_total, ans_mask_total, ans_cnt, good_mask);
    }

    auto ans_s = print_mask(ans_mask_total);

    reverse(all(ans_s));
    ans_s.resize(m);
    reverse(all(ans_s));

    cout << ans_s << endl;





	return 0;
}

