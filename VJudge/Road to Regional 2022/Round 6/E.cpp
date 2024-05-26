#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

const ld eps = 0, inf = numeric_limits<ld>::max(), pi = acos(-1);
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

int circleInsideCircle(const point & c1, ld r1, const point & c2, ld r2){
	//test if circle 2 is inside circle 1
	//returns "-1" if 2 touches internally 1, "1" if 2 is inside 1, "0" if they overlap
	ld l = r1 - r2 - (c1 - c2).length();
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

//! 0 No se tocan
//! 1 Uno está dentro 
//! 2 Esta adentro y se tocan 7u7


struct circle{
    point center;
    ld radius;
    int idx;

    circle() {}
    circle(point c, ld radius, int idx): center(c), radius(radius), idx(idx) {}

    ld getArea() {
        return pi * radius * radius;
    }

};


vector<circle> circles;
vector<bool> visited;
vector<circle> rest_circles;


void dfs(int u, vector<circle> &inside) {
    visited[u] = true;
    inside.push_back(circles[u]);

    auto circ_u = circles[u];
    for(int i = u+1; i < SZ(circles); i++) {
        if(visited[i]) continue;
        auto circ_i = circles[i];
        if(circleInsideCircle(circ_u.center, circ_u.radius, circ_i.center, circ_i.radius) != 0) {
            dfs(i, inside);
        }
    }
}


ld dfs_area(int u, int sign) {
    visited[u] = true;

    auto circ_u = rest_circles[u];

    ld area = sign*circ_u.getArea();
    // cout << u << " area inicial: " << area << endl;

    for(int i = u+1; i < SZ(rest_circles); i++) {
        if(visited[i]) continue;
        auto circ_i = rest_circles[i];
        if(circleInsideCircle(circ_u.center, circ_u.radius, circ_i.center, circ_i.radius) != 0) {
            // cout << "Aqui " << rest_circles[u].center << " mete a " << rest_circles[i].center << endl;

            ld area_inside = dfs_area(i, -sign);
            // cout << u << ": " << i << " -> " << area_inside << endl;
            area += area_inside;
        }
    }
    return area;
}



void main_(){
    lli n; cin>>n;
    circles.resize(n);
    for(int i = 0; i < n; i++) {
        point p; cin>>p.x>>p.y;
        ld r; cin>>r;
        circles[i] = circle(p, r, i);
    }

    
    sort(all(circles), [&](circle a, circle b) {
        return a.radius > b.radius;
    });

    visited.resize(n);
    vector< vector<circle> > disjoints;
    for(int i = 0; i < n; i++) {
        if(visited[i]) continue;
        vector<circle> inside;
        dfs(i, inside);
        disjoints.push_back(inside);
    }

    ld ans = 0;
    for(auto &v: disjoints) {
        // for(auto x: v) {
        //     cout << x.idx << " ";
        // }
        // cout << endl;
        ans += v[0].getArea();
        v.erase(v.begin());
    }

    for(auto &v: disjoints) {

        sort(all(v), [&](circle a, circle b) {
            return a.radius > b.radius;
        });

        
        // for(auto x: v) {
        //     cout << x.idx << " ";
        // }
        // cout << endl;
    }

    // cout << ans << endl;

    
    for(auto v: disjoints) {
        for(auto x: v)
            rest_circles.push_back(x);
    }
    
    
    sort(all(rest_circles), [&](circle a, circle b) {
            return a.radius > b.radius;
    });


    fill(all(visited), false);
    for(int i = 0; i < SZ(rest_circles); i++){
        if(visited[i]) continue;
        // cout << c.center << " - " << c.radius << " - " << c.idx << endl;
        ld area = dfs_area(i, 1);
        // scout << i << " " << rest_circles[i].getArea() << " " << area << endl;
        
        ans += area;
    }

    cout << fixed << setprecision(10) << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

