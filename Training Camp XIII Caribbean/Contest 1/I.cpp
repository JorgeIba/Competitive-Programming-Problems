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

const int MOD = 98'765'431;


lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


vector<int> operator*(const vector<int> &a, const vector<int> &b) {
    int n = SZ(a);

    vector<int> c(n);

    for(int i = 0; i < n; i++) {
        c[i] = b[a[i]];
    }
    return c;
}


void solve(){

    int n, m; cin>>n>>m;
    vector<int> A(n), B(n);

    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;

    for(auto &x: A) x--;
    for(auto &x: B) x--;


    auto c = A * B;

    set< vector<int> > perms;

    auto dfs = [&](const auto &dfs, vector<int> curr) {
        if(perms.count(curr)) return;
        perms.insert(curr);
        dfs(dfs, curr * A);
        dfs(dfs, curr * B);
    };


    auto get_cycles = [&](vector<int> &perm) {
        vector<bool> visited(n);
        int cycles = 0;
        for(int i = 0; i < n; i++) {
            if(visited[i]) continue;

            cycles++;
            int curr = i, origin = i;
            do{
                visited[curr] = true;
                curr = perm[curr];
            }while(curr != origin);
        }
        return cycles;
    };


    vector<int> I(n);
    iota(all(I), 0);
    dfs(dfs, I);

    lli ans = 0;
    for(auto perm: perms) {
        ans += powerMod(m, get_cycles(perm), MOD);
        if(ans >= MOD) ans -= MOD;
    }

    lli inv = powerMod(SZ(perms), MOD-2, MOD);

    cout << ans*inv % MOD << endl;
}


int main () {
	//fastIO();

    int t; cin>>t;
    while(t--) solve();

	return 0;
}

