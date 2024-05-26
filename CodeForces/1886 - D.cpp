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

const int MAXN = 3e5 + 1000;
lli inv[MAXN];

lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

int main () {
	fastIO();

    for(lli i = 1; i < MAXN; i++){
        inv[i] = powerMod(i, MOD-2);
    }

    int n, m; cin>>n>>m;
    string s; cin>>s;

    lli ans = 1;
    for(int i = 1; i < n; i++) {
        if(s[i] == '?')
            ans = ans * i % MOD;
    }

    auto get_ans = [&]() -> void {
        if(s[0] == '?'){
            cout << 0 << endl;
        } else {
            cout << ans << endl;
        }
        return;
    };

    get_ans();
    while(m--){
        int idx; cin>>idx; idx--;
        char new_c; cin>>new_c;

        if(idx > 0 && s[idx] == '?') {
            ans = ans * inv[idx] % MOD;
        }

        s[idx] = new_c;
        if(idx > 0 && new_c == '?') {
            ans = ans * idx % MOD;
        }

        get_ans();
    }

	

	return 0;
}

