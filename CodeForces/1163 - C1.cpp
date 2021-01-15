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

	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}


struct Line{
    point a, v;
    Line() {}
    Line(point a, point v): a(a), v(v) {}
};


int info_Lines(Line A, Line B)
{
    lli det = A.v.cross(B.v);
    if(det != 0) return 1; //They intersect
    if((A.a - B.a).cross(A.v) != 0) return -1; //They'r parallel
    return 0; //They're the same
}


int main () {
	fastIO();

    lli n; cin>>n;
    vector<point> points(n);
    for(auto &x: points) cin>>x;

    vector<Line> all_Lines;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<i; j++)
        {
            point A = points[i], B = points[j];
            all_Lines.push_back({A, A-B});
        }
    }

    vector<Line> distinct;
    for(int i = 0; i<SZ(all_Lines); i++)
    {
        bool diff = true;

        for(int j = 0; j<SZ(distinct); j++)
        {
            if(info_Lines(all_Lines[i], distinct[j]) == 0)
            {
                diff = false;
            }
        }

        if(diff) distinct.push_back(all_Lines[i]);
    }

    //for(auto x: distinct) cout << x.a << " " << x.v << endl;

    lli m = SZ(distinct);

    lli ans = m * (m - 1) / 2;

    for(int i = 0; i<m; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(info_Lines(distinct[i], distinct[j]) == -1) ans -= 1;
        }
    }

    cout << ans << endl;

    
	return 0;
}