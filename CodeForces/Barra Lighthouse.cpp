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

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	ld ang() const{
		ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
	}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

ld to_rad(ld angle) { return (angle * pi) / 180.0; }

ld to_angle(ld rad) { return (rad*180) / pi; }

lli n, X, d;
ld alpha, T;
ld velocity;

ld time_to_reach(ld angle1, ld angle2)
{
    ld diff = abs(angle1 - angle2);
    //cout << "Para cubrir " << diff << " "  << diff/velocity << endl;
    return diff / velocity;
}

ld get_time(point p)
{
    ld angle_point = to_angle(p.ang());
    ld total_time = X;
    ld ans = 0;

    ld time_lap = time_to_reach(0.0, alpha); //Esto se tarda en cubrir entre las 2 barras

    if(angle_point >= alpha/2)
    {
        ld time_first = time_to_reach(angle_point, alpha/2);
        total_time = max((ld)0.0, total_time - time_first); //Ya llegó la primera barra
        
        
        ld adding = min(time_lap, total_time);
        ans += adding;
        total_time = max((ld)0.0, total_time - adding);
    }
    else
    {
        ld time_second = time_to_reach(angle_point, -alpha/2);
        ld adding = min(time_second, total_time);
        total_time = max((ld)0.0, total_time - adding);
        ans += adding;
    }
    

    lli how_many_laps = total_time / T;
    ans += how_many_laps*time_lap; //Ya dio todas las vueltas posibles
    total_time = max((ld)0.0, total_time - how_many_laps*T);


    ld time_first_again = time_to_reach(360.0 - alpha, 0);
    total_time = max((ld)0.0, total_time - time_first_again);
    ans += total_time;

    return ans;
}


int main () {
	fastIO();

    cin>>n>>X>>alpha>>T>>d;
    velocity = 360.0 / T;

    for(int i = 0; i<n; i++)   
    {
        lli x, y; cin>>x>>y;
        point p(x,y);
        if(x*x + y*y <= d*d)
            cout << fixed << setprecision(20) << get_time(p) << endl;
        else
            cout << 0.000000000 << endl;
    }

    
	return 0;
}