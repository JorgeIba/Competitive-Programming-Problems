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

int main () {
	fastIO();
	int n, k;
	cin >> k >> n;
	vector<pii> v;
	int y_t, p_t;
	cin >> y_t >> p_t;
	v.pb({y_t, p_t});
	forn(i, n + k - 2){
		int y, p;
		cin >> y >> p;
		v.pb({y, p});
	}
	sort(all(v));
	set<int> s;
	forn(i, k - 1){
		s.insert(v[i].se);
	}
	int curr_year = v[0].fi;
	int ans = -1;
	int idx = k - 1;
	forn(i, n){
		s.insert(v[idx++].se);
		int win = *prev(s.end());
		if(win == p_t) ans = curr_year;
		s.erase(win);
		curr_year++;
	}
	if(ans == -1) cout << "unknown" << endl;
	else cout << ans << endl;
	return 0;
}

