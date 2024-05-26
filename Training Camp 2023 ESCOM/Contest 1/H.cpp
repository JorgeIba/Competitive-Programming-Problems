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



const int MAXN = 4e5 + 100;
const int MOD = 998244353;

lli fact[MAXN], invFact[MAXN];

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}


void prec(){
    fact[0] = fact[1] = 1;
    invFact[0] = invFact[1] = 1;
    for(lli i = 2; i < MAXN; i++){
        fact[i] = i * fact[i-1] % MOD;
        invFact[i] = powerMod(fact[i], MOD-2);
    }
}

lli nCr(lli n, lli r){
    if(n < 0 || r < 0 || r > n) return 0LL;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
};

int main () {
	fastIO();

    prec();

    int n, k; cin>>n>>k;

    vector<int> suff(n);
    for(auto &x: suff) cin>>x;


    vector<int> pos(n);
    forn(i, n){
        pos[suff[i]] = i;
    }


    int cnt_equal= 0;
    forn(i, n-1){
        int me = suff[i], next = suff[i+1];

        int pos_next_me = (me+1 < n ? pos[me+1] : -1);
        int pos_next_next = (next+1 < n ?  pos[next+1] : -1);

        if(pos_next_me < pos_next_next) {
            cnt_equal++;
        }
    }

    cout << nCr(k + cnt_equal, n) << endl;

	return 0;
}

