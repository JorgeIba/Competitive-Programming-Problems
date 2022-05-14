#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


const lli MOD = 998244353;

lli binPow(lli a, lli b){
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}


int main () {
	//fastIO();

    lli n; cin>>n;
    vector<lli> probs(n);
    for(auto &x: probs) cin>>x;


    lli totalProd = 1;
    for(auto x: probs) {
        totalProd = totalProd * binPow(x, MOD-2) % MOD * 100 % MOD;
    }


    lli ans = totalProd; 

    for(auto x: probs) {
        totalProd = totalProd*x % MOD * binPow(100, MOD-2) % MOD;
        ( ans +=  totalProd ) %= MOD;
    }

    cout << ans - 1 << endl;



	return 0;
}

