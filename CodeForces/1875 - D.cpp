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


void main_(){
    int n; cin>>n;

    vector<lli> nums(n);
    vector<lli> fr(n+5);
    for(auto &x: nums) {
        cin>>x;
        if(x >= n+5) continue;
        fr[x]++;
    }


    auto get_mex = [&](){
        lli mex_total = 0;
        while(fr[mex_total]) mex_total++;
        return mex_total;
    };


    vector<lli> dp(n+5, -1);
    auto f = [&](const auto &f, int mex) -> lli {
        if(mex == 0) return 0;
        
        lli &ans = dp[mex];
        if(ans != -1) return ans;

        ans = 1e15;
        for(int i = 0; i < mex; i++){
            ans = min(ans, f(f, i) + fr[i] * mex);
        }
        return ans;
    };

    cout << f(f, get_mex()) - get_mex() << endl;

    // lli mex_total = get_mex();
    // lli ans = n * mex_total;
    // lli sz = n;
    // while(true){
    //     lli best = 0, best_score = 0;
    //     lli mex = get_mex();
    //     if(get_mex() == 0) break;

    //     for(int i = 0; i < mex; i++){
    //         lli f = fr[i];
    //         lli best_i = (sz - f + 1) * (mex - i);
         
    //         if(i == 1){
    //             debugg(best_i);
    //         }

    //         if(best_score <= best_i){
    //             best = i;
    //             best_score = best_i;
    //         }
    //     }

    //     debugg(best);
    //     debugg(best_score);

    //     sz -= fr[best];
    //     fr[best] = 0;
    //     ans -= best_score;

    //     // sz -= fr[best];
    //     // fr[best] = 0;
    //     // ans += best_score;

    //     // bool ok = true;
    //     // for(int i = 0; i <= n; i++){
    //     //     if(fr[i]){
    //     //         ok = false;
    //     //     }
    //     // }
    // }

    // cout << ans << endl;

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

