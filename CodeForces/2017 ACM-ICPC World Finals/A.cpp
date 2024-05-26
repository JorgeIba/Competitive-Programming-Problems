#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

struct Point{
    lli x, y;

    Point(): x(0), y(0) {}
    Point(lli x, lli y): x(x), y(y) {}

    lli cross(const Point &P) const {
        return x * P.y - y * P.x;
    }
    lli dot(const Point &P) const {
        return x * P.x + y * P.y;
    }

    Point operator-(const Point &P) const {
        return {x - P.x, y - P.y};
    }
    Point operator+(const Point &P) const {
        return {x + P.x, y + P.y};
    }
    Point operator*(const lli &k) const {
        return {x * k, y * k};
    }

    bool operator<(const Point &P) const {
        return pair<lli,lli>{x, y} < pair<lli,lli>{P.x, P.y};
    }

    bool operator==(const Point &P) const {
        return pair<lli,lli>{x, y} == pair<lli,lli>{P.x, P.y};
    }
    bool operator!=(const Point &P) const {
        return pair<lli,lli>{x, y} != pair<lli,lli>{P.x, P.y};
    }

    bool half(const Point & p) const{return (p.cross(*this) < 0) || ((p.cross(*this) == 0) && (p.dot(*this) < 0));}
};


int sgn(lli x) {
    if(x < 0) return -1;
    else if(x > 0) return 1;
    return 0;
}


struct Fraction{
    lli x, y;
    Fraction(): x(0), y(1) {}
    Fraction(lli _x, lli _y = 1){
        lli g = gcd(labs(_x), labs(_y));
        if(_y < 0) {
            _x *= -1;
            _y *= -1;
        }

        x = _x / g;
        y = _y / g;
    }


    ld value() const {
        return (ld) x / y;
    }

    Fraction operator*(const Fraction &F) const {
        return {x * F.x, y * F.y};
    }
    Fraction operator/(const Fraction &F) const {
        return {x * F.y, y * F.x};
    }
    Fraction operator-(const Fraction &F) const {
        return {x * F.y - F.x * y, y * F.y};
    }
    Fraction operator+(const Fraction &F) const {
        return {x * F.y + F.x * y, y * F.y};
    }


    bool operator==(const Fraction &F) const {
        return x == F.x && y == F.y;
    }
    bool operator<(const Fraction &F) const {
        return x * F.y < y * F.x;
    }
    bool operator<=(const Fraction &F) const {
        return x * F.y <= y * F.x;
    }

    bool operator>(const Fraction &F) const {
        return x * F.y > y * F.x;
    }
    bool operator>=(const Fraction &F) const {
        return x * F.y >= y * F.x;
    }

    bool is_integer() const {
        return y == 1;
    }
};

Fraction intersectLines(const Point &a1, const Point &v1, const Point &a2, const Point &v2) {
    lli det = v1.cross(v2);
    Fraction t = Fraction((a2 - a1).cross(v2), det);
    // return a1 + t * v1;
    return t;
}


bool pointInLine(const Point &a, const Point &v, const Point &p) {
    return (p-a).cross(v) == 0;
}

bool pointInSegment(const Point &a, const Point &b, const Point &p) {
    return pointInLine(a, b - a, p) && (a - p).dot(b - p) <= 0;
}

bool pointInRay(const Point &a, const Point &b, const Point &p) {
    return pointInLine(a, b - a, p) && (b - a).dot(p - a) >= 0;
}


int intersectLineSegInfo(const Point &a, const Point &v, const Point &c, const Point &d) {
    Point v2 = d - c;
    lli det = v.cross(v2);
    if(det == 0) {
        if((c-a).cross(v) == 0) {
            return -1;
        } else {
            return 0;
        }
    } else {
        return sgn(v.cross(c-a)) != sgn(v.cross(d-a));
    }
}



int intersectSegInfo(const Point &a, const Point &b, const Point &c, const Point &d) {
	Point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no point
			}
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
	}
}

bool checkIfEndpoint(const Fraction &t, const Point &a, const Point &v, const vector<Point> &endPoints) {
    Fraction x = Fraction(a.x) + Fraction(v.x) * t;
    Fraction y = Fraction(a.y) + Fraction(v.y) * t;
    if(!x.is_integer() || !y.is_integer()) {
        return false; // Endpoints are integer
    } 
    Point p = Point(x.x, y.x);
    assert(x.y == 1 && y.y == 1);
    for(auto end_point: endPoints) {
        if(p == end_point) return true;
    }
    return false;
}
 

ostream& operator<<(ostream &os, const Fraction &F) {
    return os << F.x << "/" << F.y;
}


ostream& operator<<(ostream &os, const Point &F) {
    return os << "(" << F.x << "," << F.y << ")";
}


int main () {
	// fastIO();

    int n; cin>>n;
    vector< Point > points(n);

    for(auto &p: points) {
        // ll x, y; cin>>x>>y;
        cin>>p.x>>p.y;
        // p.x = x, p.y = y;
    }

    auto in_range = [&](const Point &bef, const Point &me, const Point &next, const Point &p) {
        if(pointInRay(me, next, p) || pointInRay(me, bef, p)) return true;

        Point v = next - me;
        Point o = me;
        auto cmp = [&](const Point &a, const Point &b) {
            auto left = Point((a - o).half(v), 0);
            auto right = Point((b - o).half(v), (a - o).cross(b - o));

            assert(left != right);
		    return left < right;
        };

        vector<Point> test = {next, p, bef};
        sort(all(test), cmp);

        vector<Point> check = {next, p, bef};
        return test == check;
    };


    auto is_inside = [&](int i, int j) {
        Point me = points[i];
        Point next = points[(i+1) % n];
        Point bef = points[(i-1+n) % n];

        Point other = points[j];

        if(!in_range(bef, me, next, other)) return false; // Is not in range

        for(int k = 0; k < n; k++) {
            auto p = points[k];
            auto q = points[(k+1)%n];
            auto pp = points[(k-1+n)%n];
            auto qq = points[(k+2)%n];

            auto info = intersectSegInfo(me, other, p, q);
            if(info == 1) {
                // check if inter point is different than endpoints
                Fraction t = intersectLines(me, other-me, p, q - p);

                if(!checkIfEndpoint(t, me, other-me, {me, other, p, q})){
                    return false;
                }
            } else if(info == -1) {
                if(!(pointInSegment(me, other, p) && pointInSegment(me, other, q))) {
                    cout << me << " - " << other << " -- " << p << " --- " << q << endl;
                }
                assert(pointInSegment(me, other, p) && pointInSegment(me, other, q));
                auto v = other-me;
                int t = sgn(v.cross(pp-me)), u = sgn(v.cross(qq-me));
                if(t != u) return false;
            }
        }

        return true;
    };


    ld ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(!is_inside(i, j)) continue;

            Point me = points[i];
            Point other = points[j];

            vector< Fraction > posTime, negTime;
            for(int k = 0; k < n; k++) {
                Point p = points[k];
                Point q = points[(k+1)%n];

                if(intersectLineSegInfo(me, other-me, p, q) == 1) {
                    Fraction t = intersectLines(me, other-me, p, q-p);
                    bool is_endpoint = checkIfEndpoint(t, me, other-me, {me, other, p, q});

                    if(is_endpoint) continue;
                    
                    if(t < Fraction(0)) {
                        negTime.push_back(t);
                    } else if(t > Fraction(1)){
                        posTime.push_back(t);
                    }
                }
            }

            sort(all(posTime));
            sort(all(negTime));

            Fraction left = Fraction(0);
            Fraction right = Fraction(1);

            if(SZ(posTime)) {
                right = posTime[0];
            }
            if(SZ(negTime)) {
                left = negTime.back();
            }


            assert(left <= Fraction(0) && right >= Fraction(1));

            Point a = me, v = other-me;

            // left_most = a + left * v;

            Fraction x_left = Fraction(a.x) + left * Fraction(v.x);
            Fraction y_left = Fraction(a.y) + left * Fraction(v.y);
            

            Fraction x_right = Fraction(a.x) + right * Fraction(v.x);
            Fraction y_right = Fraction(a.y) + right * Fraction(v.y);


            ld x = (x_left.value() - x_right.value());
            ld y = (y_left.value() - y_right.value());
            ld dist = sqrtl(x*x + y*y);
            ans = max(ans, dist);
        }
    }

    cout << fixed << setprecision(15) << ans << endl;



	return 0;
}