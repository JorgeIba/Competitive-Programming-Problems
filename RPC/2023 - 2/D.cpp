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

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli a, lli b): x(a), y(b) {}
	point operator-(const point& p)const{
		return point(x - p.x, y - p.y);
	}
	lli cross(const point& p) const {
		return x * p.y - y * p.x;
	}
	bool operator<(const point& p)const{
		return x < p.x || (x == p.x && y < p.y);
	}
};

vector< point > convexHull(vector< point >& P){
	vector< point > D,U;
	sort( all(P) );
	int n = P.size();
	if(n <= 2) return P;
	int i=0;
	while(i<n){
		while(D.size() >= 2 && (D[ D.size()-1 ] - D[ D.size()-2 ]).cross( P[i] - D[ D.size()-1 ] ) <= 0 )
			D.pop_back();
		D.pb( P[i] );
		i++;
	}
	i = n-1;
	while(i>=0){
		while(U.size() >= 2 && (U[ U.size()-1 ] - U[ U.size()-2 ]).cross( P[i] - U[ U.size()-1 ] ) <= 0 )
			U.pop_back();
		U.pb( P[i] );
		i--;
	}
	D.pop_back();
	U.pop_back();
	D.insert( D.end(), all(U) );
	return D;
}


bool in_same_d(vector<point>& P){
	if(SZ(P) <= 1) return false;
	lli a = P[0].y - P[1].y;
	lli b = P[0].x - P[1].x;
	if(abs(a) != abs(b)) return false;
	forr(i, 1, SZ(P) - 1){
		lli na = P[0].y - P[i].y;
		lli nb = P[0].x - P[i].x;
		if(a * nb != b * na) return false;
	}
	return true;
}

int main () {
	fastIO();
	int n;
	cin >> n;
	vector<point> P, org;
	forn(i, n){
		int x, y;
		cin >> x >> y;
		P.emplace_back(x + 1, y);
		P.emplace_back(x - 1, y);
		P.emplace_back(x, y - 1);
		P.emplace_back(x, y + 1);
		org.emplace_back(x, y);
	}
	if(n == 0){
		cout << 0 << endl;
		return 0;
	}
	if(n == 1){
		cout << 4 << endl;
		return 0;
	}
	bool same_d = in_same_d(org);
	auto v = convexHull(P);
	lli ans = SZ(v);
	if(same_d) ans++;
	if(v.empty()){
		cout << "-1" << endl;
		return 0;
	}
	forn(i, SZ(v)){
		int j = (i + 1) % v.size();
		lli aux = max({abs(v[i].x - v[j].x) - 1, abs(v[i].y - v[j].y) - 1, 0LL});
		ans += aux;
	}
	cout << ans << endl;
	return 0;
}

