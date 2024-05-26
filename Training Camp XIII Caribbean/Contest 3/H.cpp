#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define SZ(v) (int)v.size()
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

using namespace std;

typedef long long int lli;

const lli MAXN = 1e5 + 1000;
const lli MOD = 1e9 + 7;
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
vector<lli> pow_25(MAXN+1, 1), pow_26(MAXN + 1, 1);
void prec(){
    pow_25[1] = 25;
    pow_26[1] = 26;
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = i*fact[i-1] % MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i] % MOD;
        invFact[i] = inv[i]*invFact[i-1] % MOD;
        pow_25[i] = pow_25[i-1] * 25 % MOD;
        pow_26[i] = pow_26[i-1] * 26 % MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


int main(){
    fastIO();

    prec();

    int q; cin>>q;
    string s; cin>>s;
    int sz_s = SZ(s);

    vector< vector< int > > answers(MAXN);

    auto calc = [&]() {
        answers[sz_s].resize(MAXN);
        for(int i = sz_s; i < MAXN; i++) {
            lli acum_1 = 1LL*answers[sz_s][i-1] * 26 % MOD;
            lli acum_2 = 1LL*nCr(i-1, sz_s-1) * pow_25[(i-1) - (sz_s - 1)] % MOD;
            answers[sz_s][i] = (acum_1 + acum_2) % MOD;
        }
    };


    while(q--) {
        int t; cin>>t;

        if(t == 2) {
            int n; cin>>n;

            if(answers[sz_s].empty()){
                calc();
            }

            cout << answers[sz_s][n] << endl;
        } else {
            cin>>s;
            sz_s = SZ(s);
        }
    }


    return 0;
}