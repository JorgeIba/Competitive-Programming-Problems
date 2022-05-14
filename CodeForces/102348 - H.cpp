#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;

typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int MAXN = 3005;

int n;
lli A[MAXN];

int main () {
	fastIO();
	cin >> n;
	int ans = 1;
	vector<unordered_map<lli, int>> dp(n);
	forn(i, n) cin >> A[i];
	for(int i = n - 1; i >= 0; i--){
		for(int j = i + 1; j < n; j++){
			int aux = A[j] - A[i];
			dp[i][aux] = 1;
			if(dp[j].count(aux))
				dp[i][aux] += dp[j][aux];
			ans = max(ans, dp[i][aux]);
		}
	}
	cout << ans + 1 << endl;
	return 0;
}
