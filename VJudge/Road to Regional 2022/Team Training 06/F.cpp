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

const int MAXN = 5000 + 100;
ld dp[MAXN][MAXN];
bool visited[MAXN][MAXN];

int main () {
	//fastIO();
    
    int n, k; cin>>n>>k;

    vector< array<int, 3> > contracts(n);

    for(auto &[x, w, c]: contracts) cin>>x>>w>>c;

    sort(all(contracts));

    vector<int> x(n), w(n), c(n);
    forn(i, n){
        x[i] = contracts[i][0];
        w[i] = contracts[i][1];
        c[i] = contracts[i][2];
    }

    auto f = [&](const auto &f, int l, int r) -> ld {
        if(r >= n) return 0;

        ld &ans = dp[l][r];
        if(visited[l][r]) return ans;
        visited[l][r] = true;

        ld gain_finishing = 1.0l * (x[r] - x[l]) / 100.0l * (  c[l] * 0.5l + c[r] * 0.5l );
        // ld cost = (w[l] + w[r]);

        return ans = max(
            f(f, l, r+1),
            k * gain_finishing - w[r] + f(f, r, r+1)
        );
    };

    ld ans = 0;
    for(int l = 0; l < n; l++){
        ans = max(ans, f(f, l, l+1) - w[l]);
    }

    cout << fixed << setprecision(10);
    cout << ans << endl;

	return 0;
}

