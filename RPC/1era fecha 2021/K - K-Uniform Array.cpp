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

const int MAXN = 1e5 + 5;

int nxt[MAXN];
int last[MAXN];
vi queries[MAXN];
lli bit[MAXN];

int lsb(int i){
	return i & -i;
}

void update(int i, int val){
	while(i < MAXN){
		bit[i] += val;
		i += lsb(i);
	}
}

lli query(int x){
	lli res = 0;
	while(x){
		res += bit[x];
		x -= lsb(x);
	}
	return res;
}

int main () {
	fastIO();
	int n, k;
	cin >> n >> k;
	vi v(n);
	set<int> s;
	map<int, int> id;
	forn(i, n){
		cin >> v[i];
		s.insert(v[i]);
	}
	int _id = 1;
	for(auto x:s)
		id[x] = _id++;
	forn(i, n) v[i] = id[v[i]];
	/* cout << "V: {"; for(auto i:v) cout << i << ','; cout << "}\n"; */
	fill(last, last + _id, -1);
	for(int i = n - 1; i >= 0; i--){
		nxt[i] = last[v[i]];
		last[v[i]] = i;
	}
	/* cout << "nxt: {"; forn(i, n) cout << nxt[i] << ','; cout << "}\n"; */
	for(auto val:s){
		int x = id[val];
		int l, r;
		l = last[x]; r = -2;
		forn(i, k - 1){
			if(r == -1) break;
			if(r == -2) r = last[x];
			else r = nxt[r];
		}
		while(r != -1){
			if(r == -2) r = last[x];
			else r = nxt[r];
			if(r == -1) break;
			queries[r].pb(l);
			l = nxt[l];
		}
	}
	/* cout << "window finished\n"; */
	fill(last, last + _id, -1);
	int ans = n + 5;
	forn(i, n){
		if(last[v[i]] != -1)
			update(last[v[i]] + 1, -1);
		update(i + 1, 1);
		last[v[i]] = i;
		for(auto l:queries[i]){
			int aux = query(i + 1) - query(l);
			ans = min(ans, aux - 1);
		}
	}
	/* cout << var(ans) << endl; */
	if(ans > n) cout << "-1\n";
	else cout << ans << endl;
	return 0;
}
