#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


struct Fraction{
    lli x, y; 

    Fraction(){}
    Fraction(lli x): x(x), y(1) {}
    Fraction(lli num, lli den) {
        lli gcd = __gcd(num, den);
        x = num / gcd;
        y = den / gcd;
		if(y < 0) x *= -1, y *= -1;
    }

    Fraction operator+(const Fraction & p) const{return Fraction(x * p.y + p.x * y, y * p.y);}
	Fraction operator-(const Fraction & p) const{return Fraction(x * p.y - p.x * y, y * p.y);}
	Fraction operator*(const Fraction & p) const{return Fraction(x * p.x, y * p.y);}
	Fraction operator/(const Fraction & p) const{return Fraction(x * p.y, y * p.x);}


    Fraction operator+(const Fraction p) {return Fraction(x * p.y + p.x * y, y * p.y);}
	Fraction operator-(const Fraction p) {return Fraction(x * p.y - p.x * y, y * p.y);}
	Fraction operator*(const Fraction p) {return Fraction(x * p.x, y * p.y);}
	Fraction operator/(const Fraction p) {return Fraction(x * p.y, y * p.x);}

    constexpr bool operator<(const Fraction &p) const { return x * p.y < y * p.x; }
    constexpr bool operator==(const Fraction &p) const { return x * p.y == y * p.x; }
    constexpr bool operator!=(const Fraction &p) const { return !(x * p.y == y * p.x); }
    constexpr bool operator<=(const Fraction &p) const { return *this < p || *this == p; }
    constexpr bool operator>(const Fraction &p) const { return !(*this <= p);}
    constexpr bool operator>=(const Fraction &p) const { return *this > p || *this == p;}


	// bool operator<(Fraction p) { return x * p.y < y * p.x; }
    // bool operator==(Fraction p) { return x * p.y == y * p.x; }
    // bool operator!=(Fraction p) { return !(x * p.y == y * p.x); }
    // bool operator<=(Fraction p) { return *this < p || *this == p; }
    // bool operator>(Fraction p) { return !(*this <= p);}
    // bool operator>=(Fraction p) { return *this > p || *this == p;}
};

istream &operator>>(istream &is, Fraction & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const Fraction & p){return os << "(" << p.x << "/" << p.y << ")";}


using ld = Fraction;
const ld eps = Fraction(1, 1e9), inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a >= b;}     //a >= b
bool leq(ld a, ld b){return a <= b;}     //a <= b
bool ge(ld a, ld b){return a > b;}        //a > b
bool le(ld a, ld b){return a < b;}        //a < b
bool eq(ld a, ld b){return a == b;}  //a == b
bool neq(ld a, ld b){return a != b;}  //a != b

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}

	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
};
istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

Fraction intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	Fraction det = v1.cross(v2);
	Fraction time = ((a2 - a1).cross(v2) / det);
	if(time >= 0) return time;
	return -1;
}

int intersectLineSegmentInfo(const point & a, const point & v, const point & c, const point & d){
	//line a+tv, segment cd
	point v2 = d - c;
	ld det = v.cross(v2);
	if(eq(det, 0)){
		if(eq((c - a).cross(v), 0)){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single point, 0: no point
	}
}

bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return eq((p - a).cross(v), 0);
}

bool pointInSegment(const point & a, const point & b, const point & p){
	//segment ab, point p
	return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
}

bool pointInPerimeter(const vector<point> & P, const point & p){
	int n = P.size();
	for(int i = 0; i < n; i++){
		if(pointInSegment(P[i], P[(i + 1) % n], p)){
			return true;
		}
	}
	return false;
}

bool crossesRay(const point & a, const point & b, const point & p){
	return (geq(b.y, p.y) - geq(a.y, p.y)) * sgn((a - p).cross(b - p)) > 0;
}

int pointInPolygon(const vector<point> & P, const point & p){
	if(pointInPerimeter(P, p)){
		return -1; //point in the perimeter
	}
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	}
	return rays & 1; //0: point outside, 1: point inside
}



int main () {
	//fastIO();


    int n; cin>>n;
    
    lli x_1, y_1, x_2, y_2; cin>>x_1>>y_1>>x_2>>y_2;
    vector< point > corners_rect(4);

    corners_rect[0] = point(x_1, y_1);
    corners_rect[1] = point(x_2, y_1);
    corners_rect[2] = point(x_2, y_2);
    corners_rect[3] = point(x_1, y_2);

    vector< pair<point, point> > mouses(n);

    for(auto &[pos, vel]: mouses){
        lli pos_x, pos_y; cin>>pos_x>>pos_y;
        pos = point(pos_x, pos_y);
        
        lli vel_x, vel_y; cin>>vel_x>>vel_y;
        vel = point(vel_x, vel_y);
    }


	vector< pair<Fraction, Fraction> > intervals(n, pair<Fraction, Fraction>(-1, -1));


	for(int i = 0; i < n; i++){
		auto &[p_1, v_1] = mouses[i];
		if(pointInPolygon(corners_rect, p_1) == 1){
			intervals[i].first = 0;
		}
	}

	const int START = 1, END = 0;

	bool impossible = false;
	for(int i = 0; i < n; i++) {
		auto &[p_1, v_1] = mouses[i];



		vector< Fraction > times_intersections;
		if(v_1 != point(0, 0)){
			
			for(int i = 0; i < 4; i++){
				auto c = corners_rect[i], d = corners_rect[(i+1) % 4];
				auto info_intersection = intersectLineSegmentInfo(p_1, v_1, c, d);
				if(info_intersection == 1) {
					auto timee = intersectLines(p_1, v_1, c, d-c);
					if(timee != -1) times_intersections.push_back(timee);
				} else if(info_intersection == -1) {
					impossible = true;
				}
			}
		} else {
			if(pointInPolygon(corners_rect, p_1) == 1) {
				times_intersections.push_back(0);
				times_intersections.push_back(1e9);
			}
		}


		sort(all(times_intersections));
		times_intersections.erase(unique(all(times_intersections)), times_intersections.end());

		if(SZ(times_intersections) == 2){
			intervals[i].first = times_intersections[0];
			intervals[i].second = times_intersections[1];
		} else if(SZ(times_intersections) == 1) {
			if(intervals[i].first == -1) {
				impossible = true;
			}
			intervals[i].second = times_intersections[0];
		} else {
			impossible = true;
		}
	}


	vector< pair<Fraction, int> > events;
	for(auto [start, end]: intervals){
		// debugg(start);
		// debugg(end);
		events.push_back({start, START});
		events.push_back({end, END});
	}

	sort(all(events));

	int quantity = 0;
	Fraction time_start = -1, time_end = -1;
	for(auto [timee, type]: events) {
		if(type == END){
			if(quantity == n) {
				time_end = timee;
			}

			quantity--;
		} else {

			quantity++;
			if(quantity == n){
				time_start = timee;
			}
		}
	}


	if(impossible || time_start == -1 || time_start == time_end) {
		cout << -1 << endl;
		return 0;
	}


	long double ans = (long double) time_start.x / time_start.y;
	long double eps = 1e-9;


	cout << fixed << setprecision(15) << ans + eps << endl ;






	return 0;
}

