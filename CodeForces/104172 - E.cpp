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

const int MX = 1e6 + 5;
int n, k, a[MX], cn[4 * MX], st[4 * MX];
vi pos[MX];

void build (int i, int j, int pos) {
	st[pos] = j - i + 1;
	
	if (i < j) {
		int m = (i + j) / 2;
		build(i, m, pos * 2);
		build(m + 1, j, pos * 2 + 1);
	}
}

void update (int i, int j, int pos, int l, int r, int k) {
	if (j < l || r < i) return;
	
	if (l <= i && j <= r) {
		cn[pos] += k;
		
		if (cn[pos]) {
			st[pos] = 0;
		} else if (i == j) {
			st[pos] = 1;
		} else {
			st[pos] = st[pos * 2] + st[pos * 2 + 1];
		}
		
		return;
	}
	
	int m = (i + j) / 2;
	update(i, m, pos * 2, l, r, k);
	update(m + 1, j, pos * 2 + 1, l, r, k);
	
	if (cn[pos]) {
		st[pos] = 0;
	} else {
		st[pos] = st[pos * 2] + st[pos * 2 + 1];
	}
}

void main_() {
	cin >> n >> k;
	forr (i, 1, n) {
		cin >> a[i];
	}
	
	build(1, n, 1);
	
	ll res = 0;
	forr (i, 1, n) {
		pos[a[i]].pb(i);
		
		if ((int)pos[a[i]].size() >= k) {
			int r = pos[a[i]].end()[-k];
			int l = (int)pos[a[i]].size() > k ? pos[a[i]].end()[-k - 1] + 1 : 1;
			
			update(1, n, 1, l, r, 1); 
		}
		
		if ((int)pos[a[i]].size() > k) {
			int r = pos[a[i]].end()[-k - 1];
			int l = (int)pos[a[i]].size() > k + 1 ? pos[a[i]].end()[-k - 2] + 1 : 1;
			
			update(1, n, 1, l, r, -1); 
		}
		
		res += st[1] - (n - i);
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
