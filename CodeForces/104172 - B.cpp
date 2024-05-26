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

const int MX = 1005, mod = 998244353;
int n, m;
ll fil[MX][MX], col[MX][MX], izq[MX][MX], der[MX][MX], aba[MX][MX], arr[MX][MX];

void main_() {
	cin >> n >> m;
	
	forr (i, 1, n) {
		forr (j, 1, m) {
			cin >> fil[i][j];
			izq[i][j] = (izq[i][j - 1] + fil[i][j]) % mod;
		}
	}
	
	forr (i, 1, n) {
		forr (j, 1, m) {
			cin >> col[i][j];
			arr[i][j] = (arr[i - 1][j] + col[i][j]) % mod;
		}
	}
	
	for (int i = n; i >= 1; i--) {
		for (int j = m; j >= 1; j--) {
			der[i][j] = (der[i][j + 1] + fil[i][j]) % mod;
			aba[i][j] = (aba[i + 1][j] + col[i][j]) % mod;
		}
	}
	
	ll res = 2;
	forr (i, 1, n)
	forr (j, 1, m) {
		ll p = der[i + 1][j];
		(p *= aba[i][j + 1]) %= mod;
		(p *= izq[i][j - 1]) %= mod;
		(p *= arr[i - 1][j]) %= mod;
		(res += p) %= mod;
	}
	
	cout << res << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t = 1;
	// cin >> t;
	while (t--)
		main_();
	
	return 0;
}
