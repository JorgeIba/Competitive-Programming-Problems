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
const int MAXK = 1000+10;
const int MAXN = 2e5 + 100;
int dp[MAXK][4];

vector<lli> fact(MAXN + 1, 1), inv(MAXN + 1, 1), invFact(MAXN + 1, 1);
void prec() {
    for (lli i = 2; i <= MAXN; ++i) {
        fact[i] = i * fact[i - 1] % MOD;
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        invFact[i] = inv[i] * invFact[i - 1] % MOD;
    }
}

lli nCr(lli n, lli r) {
    if (n < 0 || r > n || r < 0)
        return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main () {
	fastIO();

    prec();
	
    int n, m, k; cin>>n>>m>>k;

    vector< pair<int,int> > pos(k);
    for(auto &[x, y]: pos) cin>>x>>y;

    for(auto [x, y]: pos) {
        if(x == 1 && y == 1) {
            cout << 0 << endl;
            return 0;
        }
        if(x == n && y == m) {
            cout << 0 << endl;
            return 0;
        }
    }

    pos.push_back({n, m});
    pos.insert(pos.begin(), {1, 1});

    auto ways = [&](int x, int y) {
        return nCr(x+y, y);
    };

    memset(dp, -1, sizeof(dp));
    auto f = [&](const auto &f, int idx, int sgn) -> lli {
        auto [x, y] = pos[idx];
        if(x == n && y == m) return (sgn == -1 ? MOD - 1 : 1);

        int &ans = dp[idx][sgn+1];
        if(ans != -1) return ans;

        ans = 0;
        for(int i = 0; i < SZ(pos); i++){
            auto [new_x, new_y] = pos[i];
            if(new_x == x && new_y == y) continue;
            if(new_x >= x && new_y >= y) {

                ans += 1LL * ways(new_x - x, new_y - y) * f(f, i, sgn * (-1)) % MOD;

                ans %= MOD;
            }
        }
        return ans;
    };

    cout << f(f, 0, -1) << endl;




	return 0;
}

