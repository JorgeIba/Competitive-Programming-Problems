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
#define fi first
#define se second

using namespace std;

const int MAXN = 1e5+100;

vector<int> facts_n[MAXN]; 
vector<int> divs[MAXN];
int mu[MAXN];


void prec(int n){
    for(int i = 2; i <= n; i++){
        if(facts_n[i].empty()) {
            for(int j = i; j <= n; j += i){
                facts_n[j].push_back(i);
            }
        }
    }

    forr(i, 2, n) {
        if(SZ(facts_n[i]) & 1) mu[i] = -1;
        else mu[i] = 1;
    }


    for(int i = 1; i <= n; i++){
        int m = SZ(facts_n[i]);

        for(int mask = 0; mask < (1 << m); mask++){
            int div = 1;
            for(int j = 0; j < m; j++){
                if(mask & (1 << j))
                    div *= facts_n[i][j];
            }

            divs[i].push_back(div);
        }
    }
}



int main () {
	fastIO();

    int n, q; cin>>n>>q;

    prec(1e5);

    
    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];



    vector< pair<int, int> > upds(q+1);

    forr(i, 1, q) cin>>upds[i].fi>>upds[i].se;


    
    const int LOG = 19;

    vector< pair<int,int> > limits_nums(n+1, {1, q});

    vector< int > ans(n+1, -1);
    for(int iter = 0; iter < LOG; iter++) {
        vector< vector<int> > nums_in_mid(q+1);
        vector< bool > ans_iter(n+1);


        forr(i, 1, n) {
            auto [l, r] = limits_nums[i];
            int mid = l + (r-l)/2;
            if(mid <= q)
                nums_in_mid[mid].push_back(i);
        }

        vector<lli> total_sum(MAXN);

        for(int i = 1; i <= q; i++) {
            auto [c, d] = upds[i];

            for(auto div: divs[c]) {
                total_sum[div] += d;
            }


            for(auto idx: nums_in_mid[i]) {
                auto num = nums[idx];

                lli total_sum_num = 0;
                for(auto div: divs[idx]) {
                    total_sum_num += mu[div] * total_sum[div];
                } 

                lli sum = num + total_sum_num;

                if(sum <= 0) {
                    ans_iter[idx] = true;
                } else {
                    ans_iter[idx] = false;
                }
            }
        }
    


        forr(i, 1, n){
            auto &[l, r] = limits_nums[i];
            int mid = l + (r-l)/2;
            if(ans_iter[i]){
                ans[i] = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
    }

    forr(i, 1, n) {
        cout << ans[i] << endl;
    }






	return 0;
}

