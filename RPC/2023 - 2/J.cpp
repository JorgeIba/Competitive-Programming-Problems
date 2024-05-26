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

const int MAXN = 800;

bool vis[MAXN];

void add_range(int a, int b){
	a *= 2;
	b *= 2;
	/* cout << "adding range: (" << a << ", " << b <<  ")" << endl; */
	/* if(a < b) */
		for(int i = a; i != b; i = (i + 1) % (2 * 360))
			vis[i] = true;
	/* else */
	/* 	for(int i = a; i != b; i = (i - 1 + 360) % 360) */
			/* vis[i] = true; */
	vis[b] = true;
}

bool check(){
	forn(i, 2 * 360)
		if(!vis[i]){
			/* cout << var(i) << endl; */
			return false;
		}
	return true;
}

bool add(int a, int b){
	/* cout << "(" << a << ", " << b <<  ")" << endl; */
	if(a < b){
		if(a + 180 == b) return true;
		int op1 = b - a;
		int op2 = 360 - op1;
		if(op1 < op2)
			add_range(a, b);
		else
			add_range(b, a);
	}
	else{
		if(a - 180 == b) return true;
		int op1 = a - b;
		int op2 = 360 - op1;
		if(op1 < op2)
			add_range(b, a);
		else
			add_range(a, b);
	}
	return false;
}

int main () {
	fastIO();
	int n;
	cin >> n;
	vi v;
	forn(i, n){
		int a, l;
		cin >> a >> l;
		if(l < 0) v.pb(360 + l);
		else v.pb(l);
	}
	bool flg = false;
	forn(i, n) flg |= add(v[i], v[(i + 1) % n]);
	if(flg || check()) cout << "yes" << endl;
	else cout << "no" << endl;
	return 0;
}

