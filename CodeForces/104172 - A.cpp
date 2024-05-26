#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % abs(k)) + abs(k) ) % abs(k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = int(a); i <= int(b); i++)
#define all(v) v.begin(), v.end()
#define pb push_back

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 2e5 + 5;
int n, p[MX], dp[MX];
vi to[MX];

void main_() {
	cin >> n;
	
	forr (i, 1, n) {
		to[i] = {0, 0};
	}
	
	forr (i, 1, n) {
		cin >> p[i];
	}
	
	for (int u = n; u >= 1; u--) {
		sort(all(to[u]), greater<int>());
		dp[u] = max(to[u][0], to[u][1] + 1);
		to[p[u]].pb(dp[u]);
	}
	
	cout << dp[1] << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t = 1;
	cin >> t;
	while (t--)
		main_();
	
	return 0;
}
