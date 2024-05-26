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


struct point{
    lli x, y;
    point(): x(0), y(0) {}
    point(lli x, lli y): x(x), y(y) {}
    point operator+(const point &p) const { return  {x + p.x, y + p.y}; }
    point operator-(const point &p) const { return  {x - p.x, y - p.y}; }

    lli dot(const point &p) const { return x*p.x + y*p.y; }
    lli cross(const point &p) const { return x*p.y - y*p.x; }

    bool operator==(const point &p) const { return  x == p.x && y == p.y;  }
    bool operator<(const point &p) const { return x < p.x || (x == p.x && y < p.y); }
};

ostream &operator<<(ostream &os, const point &p) {
    return os << "(" << p.x << ", " << p.y << ")";
}


int sgn(lli x) {
    if(x > 0) return 1;
    if(x < 0) return -1;
    return 0;
}

typedef vector<point> polygon;
struct convex_container{
    polygon pol;
 
    // Polygon MUST be in counter clockwise order
    convex_container(polygon p) : pol(p){
        int pos = 0;
 
        for (int i = 1; i < SZ(p); ++i){
            if (p[i].y < p[pos].y ||
                (p[i].y == p[pos].y && p[i].x < p[pos].x))
                pos = i;
        }
 
        rotate(pol.begin(), pol.begin() + pos, pol.end());
    }
 
    bool contains(point p){
        point c = pol[0];
 
        if (p.y < c.y || (pol.back() - c).cross(p - c) > 0)
            return false;
 
        int lo = 1, hi = SZ(pol) - 1;
 
        while (lo + 1 < hi){
            int m = (lo + hi) / 2; 
            if ((pol[m] - c).cross(p - c) >= 0)
                lo = m;
            else
                hi = m;
        }

        return (pol[lo + 1] - pol[lo]).cross(p - pol[lo]) >= 0;
    }
};


vector<point> minkowskiSum(vector<point> A, vector<point> B) {
    int na = SZ(A), nb = SZ(B);
    if(A.empty() || B.empty()) return {};

    rotate(A.begin(), min_element(all(A)), A.end());
    rotate(B.begin(), min_element(all(B)), B.end());

    int pa = 0, pb = 0;
    vector<point> M;

    while(pa < na && pb < nb) {
        M.push_back(A[pa] + B[pb]);
        lli x = (A[(pa+1) % na] - A[pa]).cross( B[(pb + 1) % nb] - B[pb] );
        if(x <= 0) pb++;
        if(x >= 0) pa++;
    }

    while(pa < na) M.push_back(A[pa++] + B[0]);
    while(pb < nb) M.push_back(B[pb++] + A[0]);

    return M;
}


int main () {
	fastIO();

    int na; cin>>na;
    vector<point> A(na);
    for(auto &p: A) cin>>p.x>>p.y;

    int nb; cin>>nb;
    vector<point> B(nb);
    for(auto &p: B) cin>>p.x>>p.y;

    int nc; cin>>nc;
    vector<point> C(nc);
    for(auto &p: C) cin>>p.x>>p.y;


    auto M = minkowskiSum(A, B);
    M = minkowskiSum(C, M);


    int q; cin>>q;

    convex_container *cp = new convex_container(M);

    
    while(q--) {
        point p_test; cin>>p_test.x>>p_test.y;
        p_test.x *= 3LL;
        p_test.y *= 3LL;

        if( cp->contains(p_test) ) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

	
	return 0;
}


