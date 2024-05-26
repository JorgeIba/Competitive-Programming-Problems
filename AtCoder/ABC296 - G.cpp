#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;



const lli eps = 0;
// For use with integers, just set eps=0 and everything remains the same
bool geq(lli a, lli b){return a-b >= -eps;}     //a >= b
bool leq(lli a, lli b){return b-a >= -eps;}     //a <= b
bool ge(lli a, lli b){return a-b > eps;}        //a > b
bool le(lli a, lli b){return b-a > eps;}        //a < b
bool eq(lli a, lli b){return abs(a-b) <= eps;}  //a == b
bool neq(lli a, lli b){return abs(a-b) > eps;}  //a != b


struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator>(const point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}


int pointInConvexPolygon(const vector<point> & P, const point & p, int right){
	if(p < P[0] || P[right] < p) return 0;
	int orientation = sgn((P[right] - P[0]).cross(p - P[0]));
	if(orientation == 0){
		if(p == P[0] || p == P[right]) return -1;
		return (right == 1 || right + 1 == P.size()) ? -1 : 1;
	}else if(orientation < 0){
		auto r = lower_bound(P.begin() + 1, P.begin() + right, p);
		int det = sgn((p - r[-1]).cross(r[0] - r[-1])) - 1;
		if(det == -2) det = 1;
		return det;
	}else{
		auto l = upper_bound(P.rbegin(), P.rend() - right - 1, p);
		int det = sgn((p - l[0]).cross((l == P.rbegin() ? P[0] : l[-1]) - l[0])) - 1;
		if(det == -2) det = 1;
		return det;
	}
}


void main_(){
	int n; cin>>n;
	vector< point > poly(n);
	for(auto &p: poly) cin>>p.x>>p.y;

	rotate(poly.begin(), min_element(poly.begin(), poly.end()), poly.end());
	int right = max_element(poly.begin(), poly.end()) - poly.begin();

	int q; cin>>q;
	while(q--){
		point p; cin>>p.x>>p.y;

		auto test = pointInConvexPolygon(poly, p, right);

		if(test == 1) {
			cout << "IN" << endl;
		} else if(test == -1) {
			cout << "ON" << endl;
		} else{
			cout << "OUT" << endl;
		}	
	}

}


int main () {
	//fastIO();
	
	int t = 1;
//	cin>>t;
	
	while(t--) main_();


	return 0;
}

