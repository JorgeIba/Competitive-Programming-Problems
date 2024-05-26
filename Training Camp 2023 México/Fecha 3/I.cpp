#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

// lli multMod(lli a, lli b, lli mod){
//     lli res = 0;
//     while(b){
//         if(b&1) res = (res + a) % mod;
//         b >>= 1;
//         a = (a + a) % mod;
//     }
//     return res;
// }

const lli MOD = 1e9+7, MOD2 = 1e8 + 7;
lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


void main_(){
    int n, p; cin>>n>>p;

    vector<int> powers(n);
    for(auto &x: powers) cin>>x;

    sort(all(powers));
    reverse(all(powers));

    int ans_mod = 0, ans_mod2 = 0;
    for(int i = 0; i < n; i++){
        auto pot = powers[i];
        if(ans_mod == 0 && ans_mod2 == 0) {
            ans_mod = (ans_mod + powerMod(p, pot, MOD));
            if(ans_mod >= MOD) ans_mod -= MOD;


            ans_mod2 = (ans_mod2 + powerMod(p, pot, MOD2));
            if(ans_mod2 >= MOD) ans_mod2 -= MOD2;
        } else {
            ans_mod = (ans_mod - powerMod(p, pot, MOD));
            if(ans_mod < 0) ans_mod += MOD;

            ans_mod2 = (ans_mod2 - powerMod(p, pot, MOD2));
            if(ans_mod2 < 0) ans_mod2 += MOD2;
        }
    }

    cout << ans_mod << endl;
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

