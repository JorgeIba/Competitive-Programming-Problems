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


const int MOD = 998244353;


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
    int n; cin>>n;

    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];


    vector<int> b(n+1);
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j += i){
            b[i] = max(b[i], nums[j]);
        }
    }


    vector<int> bs;
    forr(i, 1, n) bs.push_back(b[i]);

    sort(all(bs));
    lli ans = 0;
    for(int i = 0; i < n; i++){
        auto b_i = bs[i];
        int lower = i;
        (ans += 1LL * b_i * powerMod(2, lower) % MOD) %= MOD;
    }
    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

