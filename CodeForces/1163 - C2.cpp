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
	lli cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

lli INF = 1e15;

lli Gauss(lli n)
{
    return (n*(n+1))/2;
}

int main () {
	fastIO();

    lli n; cin>>n;
    vector<point> points(n);
    for(auto &x: points) cin>>x;

    set< tuple<lli,lli,lli> > Lines;

    vector< tuple<lli,lli,lli> > diff;

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<i; j++)
        {
            point A = points[i], B = points[j];

            lli a = B.y - A.y, b = A.x - B.x, c = A.cross(B);
            lli gcd = __gcd(a, __gcd(b, c));
            a/=gcd, b/=gcd, c /=gcd;

            if(!Lines.count({a, b, c})) diff.push_back({a, b, c});
            Lines.insert({a,b,c});
        }
    }

    /*
    cout << endl;
    for(auto x: diff) cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
    cout << endl;
    */

    lli ans = Gauss(SZ(diff)-1);

    map<ld, lli> slopes;

    for(int i = 0; i<SZ(diff); i++)
    {
        lli a = get<0>(diff[i]), b = get<1>(diff[i]);
        ld slope = (b? (ld)-a/b : INF);

        //cout << slope << endl;
        if(slopes.count(slope)) ans -= slopes[slope];
        slopes[slope]++;
    }
    cout << ans << endl;

    
	return 0;
}