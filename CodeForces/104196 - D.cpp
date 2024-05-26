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

const ld eps = 1e-15, pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

template<typename T>
struct Point{
    T x, y;

    Point(): x(0), y(0) {}
    Point(T x, T y): x(x), y(y) {}

    T cross(const Point &P) const { return x * P.y - y * P.x; }
    T dot(const Point &P) const{ return x * P.x + y * P.y; }

    Point operator-(const Point &P) const { return {x - P.x, y - P.y}; }

    Point<ld> operator*(const ld k) const { return {x*k, y*k}; }

    ld length() const { return sqrtl(x*x + y*y); }

    T length2() const { return x*x + y*y; }

    ld ang() const{ ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a; }

    ld ang(const Point &P) const{ return abs(ang() - P.ang()); }
};

template <typename T>
ostream &operator<<(ostream &os, const Point<T> & p){return os << "(" << p.x << ", " << p.y << ")";}

// A is in middle
ld area_conic(Point<ld> A, Point<ld> B, Point<ld> C){
    ld A1 = (B-A).cross(C-A) / 2;

    ld theta = (C-A).ang(B-A);
    if(ge(theta, pi))
        theta = 2*pi - theta;

    ld sin_theta = 2*sinl(theta);

    if(eq(sin_theta*sin_theta,0)) return 0;

    ld r2 = (B-C).length2() / (sin_theta*sin_theta);
    ld ans = A1 + r2 * (theta - sinl(2*theta)/2);

    return ans;
}

int main () {
	fastIO();

    int x_0, y_0, r; cin>>x_0>>y_0>>r;

    Point<lli> C(x_0, y_0);

    int n; cin>>n;

    vector< Point<lli> > Poly(n);
    for(auto &p: Poly) cin>>p.x>>p.y;
    for(auto &p: Poly) p = p - C;


    vector< Point<ld> > mirror(n);
    forn(i, n){
        auto p = Poly[i];
        
        mirror[i] = p * ( (ld) r*r / p.length2());
    }

    Point<ld> C_d = Point<ld>(0, 0);

    ld ans = 0;
    for(int i = 0; i < n; i++){
        auto p_b = Poly[i], p_c = Poly[(i+1)%n];
        auto pc_b = mirror[i], pc_c = mirror[(i+1)%n];
        
        if(p_b.cross(p_c) == 0) continue;
        
        if(p_b.cross(p_c) < 0) ans += area_conic(C_d, pc_c, pc_b);
        else if(p_b.cross(p_c) > 0) ans -= area_conic(C_d, pc_b, pc_c);
    }
    cout << fixed << setprecision(20) << abs(ans) << endl;


	return 0;
}

