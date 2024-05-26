#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long long int
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


const ld eps = 0;

bool geq(ld a, ld b){ return a-b >= -eps; }
bool leq(ld a, ld b){ return b-a >= -eps; }
bool ge(ld a, ld b){  return a-b  > eps; }
bool le(ld a, ld b){  return b-a  > eps; }
bool eq(ld a, ld b){  return abs(a-b) <= eps; }
bool neq(ld a, ld b){ return abs(a-b) > eps; }


struct point {
    ld x, y;
    point(): x(0), y(0) {}
    point(ld x, ld y): x(x), y(y) {}


    ld dot(const point &p) const { return x * p.x + y * p.y; }
    ld cross(const point &p) const { return x * p.y - y * p.x; }

    point operator+(const point &p) const { return {x + p.x, y + p.y}; }
    point operator-(const point &p) const { return {x - p.x, y - p.y}; }

    bool operator==(const point &p) const { return eq(x, p.x) && eq(y, p.y);  }
    bool operator!=(const point &p) const { return !(*this == p); }
    long double length() const{return sqrtl(x * x + y * y);}

    bool operator<(const point &p)  const { return le(x, p.x) || (eq(x,p.x) && le(y, p.y)); }

};

ostream &operator<<(ostream &os, const point &p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

vector<point> minkowskiSum(vector<point> A, vector<point> B) {
    int na = SZ(A), nb = SZ(B);
    if(!na || !nb) return {};

    rotate(A.begin(), min_element(all(A)), A.end());
    rotate(B.begin(), min_element(all(B)), B.end());

    int pa = 0, pb = 0;
    vector<point> M;
    while(pa < na && pb < nb) {
        M.push_back(A[pa] + B[pb]);
        ld x = ( A[ (pa + 1) % na ] - A[pa] ).cross( B[(pb + 1) % nb] - B[pb] );
        if(leq(x, 0)) pb++;
        if(geq(x, 0)) pa++;
    }

    while(pa < na) M.push_back(A[pa++] + B[0]);
    while(pb < nb) M.push_back(B[pb++] + A[0]);

    return M;
}


long double distancePointLine(const point & a, const point & v, const point & p){
	return abs(v.cross(p - a)) / v.length();
}

long double distancePointSegment(point a, point b, point p) { 
	if ((b - a).dot(p - a) < 0) return (a - p).length(); 
	if ((a - b).dot(p - b) < 0) return (b - p).length();
	return distancePointLine(a, b-a, p);
}

int main () {
	fastIO();

    int n, m; cin>>n>>m;

    vector< point > airport(n);
    for(auto &p: airport) cin>>p.x>>p.y;

    vector< point > cloud(m);
    for(auto &p: cloud) cin>>p.x>>p.y;


    for(auto &p: cloud) {
        p.x = -p.x;
        p.y = -p.y;
    }
    auto M = minkowskiSum(airport, cloud);

    point origin(0,0);

    long double ans = 1e9;
    int t = SZ(M);
    for(int i = 0; i < t; i++) {
        int next = (i+1) % t;
        long double dist = distancePointSegment(M[i], M[next], origin);
        ans = min(ans, dist);
    }

    
    cout << fixed << setprecision(10) << max((long double)0, ans - 60) << endl;

	return 0;
}

