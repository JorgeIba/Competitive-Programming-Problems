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

const int MAXN = 1e5+50;
vector<int> facts_n[MAXN];
void prec(int n){
    vector<int> is_prime(n+1, true);
    for(int i = 2; i <= n; i += 2) facts_n[i].push_back(2), is_prime[i] = false;
    is_prime[2] = true;


    for(int i = 3; i <= n; i++){
        if(is_prime[i]){
            facts_n[i].push_back(i);
            for(int j = 2*i; j <= n; j += i){
                facts_n[j].push_back(i);
                is_prime[j] = false;
            }
        }
    }
}

vector<int> divs_vec[MAXN];
vector<pair<int, lli>> queries_div[MAXN];
int nums[MAXN];
vector<int> getDivs(const vector<int> &factors)
{
    int n = SZ(factors);
    int factors_count = 1LL << n;
    vector<int> divs; 
    divs.reserve(factors_count);
    divs.push_back(1);
    for(int i = 0; i < n; i++){
        int m = SZ(divs);
        auto p = factors[i];
        for(int j = 0; j < m; j++){
            divs.push_back( divs[j] * p );
        }
    }
    return divs;
}



int main () {
	// fastIO();
	
    prec(MAXN-10);

    int n, q; cin>>n>>q;

    forn(i, n) cin>>nums[i];

    vector< pair<int,int> > queries(q);
    for(auto &x: queries) cin>>x.first>>x.second;


    for(int i = 0; i < q; i++){
        auto &[c, d] = queries[i];

        auto &divs = divs_vec[c];
        if(divs.empty())
            divs = getDivs(facts_n[c]);

        for(auto &div: divs) {
            if(div == 1) continue;
            queries_div[ div ].push_back({i+1, d});
        }
    }


    for(int i = 0; i < MAXN; i++){
        auto &vec = queries_div[i];
        int k = SZ(vec);

        for(int j = 1; j < k; j++){
            vec[j].second += vec[j-1].second;
        }
    }

    const lli INF = 1e18;

    auto check = [&](int k, int num, lli points){

        auto &divs = divs_vec[num];
        if(divs.empty())
            divs = getDivs(  facts_n[num]  );

        lli total = 0;
        for(auto div: divs){
            if(div == 1) continue;
            if(queries_div[div].empty()) continue;

            lli sum = 0;

            pair<int,lli> query = {k, INF};
            auto idx = upper_bound(all( queries_div[  div  ]  ), query) - queries_div[div].begin();

            if(idx == 0) continue;
            
            sum = queries_div[div][idx - 1].second;
            int mult = SZ(  facts_n[div]  ) & 1 ? -1 : 1;
            total += 1LL * mult * sum;
        }

        return points + total <= 0;
    };


    vector<int> total_ans(n, -1);
    for(int i = 2; i <= n; i++){
        auto num = nums[i-1];
        int l = 1, r = q, ans = -1;
        while(l <= r){
            int mid = l + (r-l)/2;
            if(  check(mid, i, num)   ) {
                ans = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }

        total_ans[i-1] = ans;
    }


    for(auto &x: total_ans) cout << x << endl;

	return 0;
}
