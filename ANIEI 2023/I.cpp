#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MOD = 1e9+7;

void main_(){
    int n, a, b; cin>>n>>a>>b;

    vector<int> dp(n+1, -1);
    auto f = [&](const auto &f, int idx) {
        if(idx == n) return 1;

        int &ans = dp[idx];
        if(ans != -1) return ans;

        // int yes = 1LL * f(f, idx+1) * a % MOD;
        // int no = 1LL * f(f, idx+1) * b  % MOD;
        // int neither = f(f, idx+1);



        return ans = 1LL*f(f, idx+1) * (a + b + 1) % MOD;
    };
    cout << f(f, 0) << endl;
}

int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

