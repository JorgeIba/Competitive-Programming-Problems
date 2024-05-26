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

	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
    ld norm() const{return x * x + y * y;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
    bool operator!=(const point & p) const{return !(*this == p);}
};

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
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

int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
	//segment ab, segment cd
	point v1 = b - a, v2 = d - c;
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

vector<point> cutPolygon(const vector<point> & P, const point & a, const point & v){
	//returns the part of the convex polygon P on the left side of line a+tv
	int n = P.size();
	vector<point> lhs;
	for(int i = 0; i < n; ++i){
		if(geq(v.cross(P[i] - a), 0)){
			lhs.push_back(P[i]);
		}
		if(intersectLineSegmentInfo(a, v, P[i], P[(i+1)%n]) == 1){
			point p = intersectLines(a, v, P[i], P[(i+1)%n] - P[i]);
			if(p != P[i] && p != P[(i+1)%n]){
				lhs.push_back(p);
			}
		}
	}
	return lhs;
}

ld area(vector<point> & P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; i++){
		ans += P[i].cross(P[(i + 1) % n]);
	}
	return abs(ans / 2);
}

const ld INF = 100000;
ld touches(const vector<point> &P, const vector<point> &Q, const point vel) {
    ld t = INF;
    int n = SZ(P);
    int m = SZ(Q);

    // P moves with velocity = vel

    // Check if point in P touches segment in Q
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            auto info = intersectLineSegmentInfo(P[i], vel, Q[j], Q[(j+1)%m]);
            if(info == 0) continue;
            else if(info == -1) {
                ld t_1v = (Q[j] - P[i]).dot(vel);
                ld t_2v = (Q[(j+1)%m] - P[i]).dot(vel);


                ld t_1;

                if(t_1v < 0 && t_2v < 0) continue;
                else if(t_1v < 0) t_1 = t_2v;
                else if(t_2v < 0) t_1 = t_1v;
                else t_1 = min(t_1v, t_2v);

                t = min(t, t_1 / vel.norm());
            } else {
                point a_1 = P[i];
                point a_2 = Q[j];
                point v_2 = (Q[(j+1)%m] - a_2);

                ld t_1 = (a_2 - a_1).cross(v_2);
                t_1 /= vel.cross(v_2);

                if(le(t_1, 0)) continue;

                t = min(t, t_1);
            }
        }
    }

    return t;
}


int main () {
	//fastIO();
	
    int n; cin>>n;
    vector< point > Poly_1(n);
    forn(i, n){
        int x, y; cin>>x>>y;
        Poly_1[i].x = x;
        Poly_1[i].y = y;
    }

    point v_1; cin>>v_1.x>>v_1.y;

    int m; cin>>m;
    vector< point > Poly_2(m);
    forn(i, m){
        int x, y; cin>>x>>y;
        Poly_2[i].x = x;
        Poly_2[i].y = y;
    }

    point v_2; cin>>v_2.x>>v_2.y;
    v_2  = v_2 - v_1;


    auto get_intersection = [&](vector<point> P, vector<point> Q) {
        forn(i, n){
            auto p = P[i];
            auto p_next = P[(i+1)%n];
            Q = cutPolygon(Q, p, (p - p_next));
        }
        return area(Q);
    };

    auto f = [&](ld t) {
        auto P1_moved = Poly_1;
        auto P2_moved = Poly_2;

        for(auto &p: P2_moved) {
            p = p + v_2*t;
        }
        auto area = get_intersection(P1_moved, P2_moved);
        return area;
    };


    ld t_1 = touches(Poly_2, Poly_1, v_2);
    ld t_2 = touches(Poly_1, Poly_2, v_2 * (-1));

    t_1 = (eq(t_1, INF) ? -1 : t_1);
    t_2 = (eq(t_2, INF) ? -1 : t_2);

    ld T = -1;
    if(t_1 < 0 && t_2 < 0) {}
    else if(t_1 < 0) T = t_2;
    else if(t_2 < 0) T = t_1;
    else T = min(t_1, t_2);


    if(le(T, 0)){
        cout << "never" << endl;
        return 0;
    }


    ld l = T, r = INF;
    while(r-l > eps){
        ld l_1 = l + (r-l) / 3;
        ld r_1 = r - (r-l) / 3;

        ld f_l = f(l_1);
        ld f_r = f(r_1);

        if(le(f_l, f_r)) {
            l = l_1;
        } else {
            r = r_1;
        }
    }

    // cout << fixed << setprecision(20) << f(r) << endl;
    cout << fixed << setprecision(20) << r << endl;

	return 0;
}

