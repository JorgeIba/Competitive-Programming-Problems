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
    for(auto &x: nums) cin>>x;


    vector< array<lli, 2> > dp(n+1, {-1,-1});

    auto f = [&](const auto &f, int idx, bool ok) -> lli {
        if(idx == n) return 0;

        lli &ans = dp[idx][ok];
        if(ans != -1) return ans;

        ans = 0;
        if(ok){
            ans = max(f(f, idx+1, ok) + nums[idx], f(f, idx+1, ok));
        } else {
            if(idx % 2 == 1){
                ans = max(f(f, idx+1, false), f(f, idx+1, true));
            } else {
                ans = max(f(f, idx+1, false), f(f, idx+1, true) + nums[idx]);
            }
            
        }
        return ans;
    };


    cout << f(f,0,false) << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

