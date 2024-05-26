#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;
 
typedef vector<lli> VLL;
typedef vector<int> VI;

const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct Point{
	ld x, y;
	Point(): x(0), y(0){}
	Point(ld x, ld y): x(x), y(y){}

	Point operator+(const Point & p) const{return Point(x + p.x, y + p.y);}
	Point operator-(const Point & p) const{return Point(x - p.x, y - p.y);}

	ld dot(const Point & p) const{return x * p.x + y * p.y;}
	ld cross(const Point & p) const{return x * p.y - y * p.x;}
    ld length() const{return sqrtl(x * x + y * y);}

	bool operator==(const Point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const Point & p) const{return !(*this == p);}
	bool operator<(const Point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
};

istream &operator>>(istream &is, Point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const Point & p){return os << "(" << p.x << ", " << p.y << ")";}

ld distance(Point a1, Point a2)
{
    return (a1-a2).length();
}

vector<Point> convexHull(vector<Point> P){
	sort(P.begin(), P.end());
	vector<Point> L, U;
	for(int i = 0; i < (int)P.size(); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}
 
int main () {
	fastIO();
    lli n; cin>>n;
    vector<Point> P(n);
    for(auto &p: P) cin>>p;

    cout << fixed << setprecision(7);

    if( n == 2)
    {
        cout << distance(P[0], P[1]) << endl;
        return 0;
    }

    auto CH = convexHull(P);
    ld ans = 0;
    n = SZ(CH);
    int j = 1;
    for(int i = 0; i<n; i++)
    {
        while(distance(CH[i], CH[j]) < distance(CH[i], CH[(j+1)%n])) j = (j+1)%n;
        ans = max(ans, distance(CH[i], CH[j]));
    }
    cout << ans << endl;

	return 0;
}