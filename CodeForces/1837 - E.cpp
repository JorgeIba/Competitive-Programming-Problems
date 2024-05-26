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


const int MOD = 998244353, MAXN = (1 << 19) + 100;
int fact[MAXN + 100];
void prec() {
    fact[0] = 1;
    for(int i = 1; i <= MAXN; i++) {
        fact[i] = 1LL * i * fact[i-1] % MOD;
    }
}


lli powerMod(lli a, lli b){
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

int main () {
	//fastIO();

    prec();
	
    int K; cin>>K;
    vector<int> pos((1<<K));

    for(auto &x: pos) cin>>x;

    lli ans = 1;
    for(int k = K; k >= 1; k--){
        int gr = 0, lo = 0;
        int limit = (1 << (k-1));
        int free_pair = 0;
        int n = (1 << k);


        for(int i = 0; i < n-1; i += 2) {
            if(pos[i] != -1 && pos[i+1] != -1) {
                bool both_gr = pos[i] >  limit && pos[i+1] >  limit;
                bool both_lo = pos[i] <= limit && pos[i+1] <= limit;
                if(both_gr || both_lo) {
                    cout << 0 << endl;
                    return 0;
                }
            }

            if(pos[i] == -1 && pos[i+1] == -1) free_pair++;

            if(pos[i]   != -1 && pos[i]   > limit) gr++;
            if(pos[i+1] != -1 && pos[i+1] > limit) gr++;

            if(pos[i]   != -1 && pos[i]   <= limit) lo++;
            if(pos[i+1] != -1 && pos[i+1] <= limit) lo++;


            if(pos[i]   != -1 &&   pos[i] <= limit) pos[i/2] = pos[i];
            else if(pos[i+1] != -1 && pos[i+1] <= limit) pos[i/2] = pos[i+1];
            else pos[i/2] = -1;
        }

    
        int predicted = (1 << (k-1)) - gr;

        ans = ans * powerMod(2, free_pair) % MOD * fact[predicted] % MOD;

        pos.resize((1 << (k-1)));
    }

    cout << ans << endl;


	return 0;
}

