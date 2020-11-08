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

const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	point operator+=(const point & p){*this = *this + p; return *this;}
	point operator-=(const point & p){*this = *this - p; return *this;}
	point operator*=(const ld & p){*this = *this * p; return *this;}
	point operator/=(const ld & p){*this = *this / p; return *this;}

	point rotate(const ld & a) const{return point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a));}
	point perp() const{return point(-y, x);}
	ld ang() const{
		ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
	}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	ld norm() const{return x * x + y * y;}
	ld length() const{return sqrtl(x * x + y * y);}
	point unit() const{return (*this) / length();}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator>(const point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

void polarSort(vector<pair<point,lli>>& P, const point & o, const point & v){
	//sort points in P around o, taking the direction of v as first angle
	sort(P.begin(), P.end(), [&](const pair<point,lli> & a, const pair<point,lli> & b){
		return point((a.fi - o).half(v), 0) < point((b.fi - o).half(v), (a.fi - o).cross(b.fi - o));
	});
}

int n;
lli tot;
vector<pair<point,lli>> P;

lli get_difference(int k, point a, point b, lli x){
	P.erase(P.begin()+k);
	vector<pair<point,lli>> monuments = P;
	polarSort(monuments,a,b);
//	for(auto i:monuments)
////		cout << i.fi << endl;
	int j = 0;
	lli ans = 1e18;
	lli sum = 0;
	forn(i,monuments.size()){
		point div = monuments[i].fi - a;
//		cout << "div: " << div << endl;
		while( div.cross(monuments[j].fi - a) >= 0 ){
//			cout << "j: " << j  << " "<< monuments[j].fi-a << " cross: " << div.cross(monuments[j].fi - a) << endl;
			sum += monuments[j].se;
			j = (j+1) % monuments.size();
			if(j == i)
				break;
		}
		lli side_a = tot - sum;
		lli side_b = sum - monuments[i].se;
//		cout << "side_a: " << side_a << " side_b: " << side_b << endl;
		lli diff = abs(side_a-side_b);
		ans = min(ans,diff);
		sum -= monuments[i].se;
	}
	P.insert(P.begin()+k, make_pair(a,x) );
	return ans;
}

lli solve(){
	lli ans = 1e18;
	forn(i,n){
//		cout << "pivot: " << i << endl;
		tot -= P[i].se;
		ans = min(ans, get_difference(i, P[i].fi, P[(i+1)%n].fi, P[i].se));
		tot += P[i].se;
	}
	return ans;
}

int main () {
	fastIO();
	cin >> n;
	P.resize(n);
	forn(i,n){
		cin >> P[i].fi >> P[i].se;
		tot += P[i].se;
	}
	cout << solve() << endl;
	return 0;
}
