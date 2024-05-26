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
	int n;
	cin >> n;
	map<string,int> cnt;
	forn(i, n){
		string name;
		cin >> name;
		cnt[name]++;
	}
	vector<pair<string,int>> v(all(cnt));
	sort(all(v), [&](const pair<string,int>& a, const pair<string,int>& b){
			return a.se > b.se;
			});
	/* for(auto s:cnt) cout << s.fi << endl; */
	vector<string> ans;
	if(2 * v[0].se > n){
		cout << SZ(cnt) - 1 << endl;
		forr(i, 1, SZ(cnt) - 1)
			ans.pb(v[i].fi);
		sort(all(ans));
		for(auto s:ans)
			cout << s << endl;
	}
	else if(v.back().se == v[0].se && SZ(v) > 1){
		cout << SZ(cnt) << endl;
		for(auto s:cnt) cout << s.fi << endl;
	}
	else{
		auto vc = v;
		int aux = 0;
		int mn_kill = 0;
		while(!v.empty()){
			/* if(2 * (v.back().se + aux) > n) break; */
			int mn = v.back().se;
			int aux2 = 0;
			while(!v.empty() && v.back().se == mn){
				aux2 += v.back().se;
				/* ans.pb(v.back().fi); */
				/* cout << v.back().fi << endl; */
				v.pop_back();
			}
			if(!v.empty() && (mn + aux) <= v.back().se)
				mn_kill = mn;
			aux += aux2;
		}
		while(!vc.empty() && vc.back().se <= mn_kill){
			ans.pb(vc.back().fi);
			vc.pop_back();
		}
		sort(all(ans));
		cout << SZ(ans) << endl;
		for(auto s:ans) cout << s << endl;
	}
	return 0;
}
