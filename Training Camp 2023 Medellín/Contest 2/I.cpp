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

const int MOD = 1e9+7;

const int MAXN = 100;
lli dp[MAXN + 10][2];

int k, d;
lli f(lli n, bool ok){
    if(n < 0) return 0;
    if(n == 0) return ok;

    lli &ans = dp[n][ok];
    if(ans != -1) return ans;

    ans = 0;
    for(int i = 1; i <= k; i++) {
        (ans += f(n - i, ok || (i >= d))) %= MOD;
    }

    return ans;
}


int main () {
	//fastIO();
	
    int n; cin>>n>>k>>d;

    memset(dp, -1, sizeof(dp));

    cout << f(n, 0) << endl;

	return 0;
}

