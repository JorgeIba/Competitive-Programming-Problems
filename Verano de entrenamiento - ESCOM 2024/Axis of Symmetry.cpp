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


struct point{
    lli x, y;

    point() {}
    point(lli x, lli y): x(x), y(y) {}

    lli cross(const point &p) const {
        return x * p.y - y * p.x;
    }

    lli dot(const point &p) const {
        return x * p.x + y * p.y;
    }

    point operator+(const point &p) const {
        return {x + p.x, y + p.y};
    }

    point operator*(const lli &k) const {
        return {x*k, y*k};
    }

    point operator/(const lli &k) const {
        return {x/k, y/k};
    }

    point operator-(const point &p) const {
        return {x - p.x, y - p.y};
    }

    point perp() const {
        return {-y, x};
    }

    bool operator==(const point &p) const {
        return pair<lli,lli>{x,y} == pair<lli,lli>{p.x, p.y};
    }
    bool operator<(const point &p) const {
        return pair<lli,lli>{x,y} < pair<lli,lli>{p.x, p.y};
    }
};


bool point_in_line(point a, point v, point p) {
    point a2 = a + v;
    return (p-a).cross(p-a2) == 0;
}

ostream &operator<<(ostream &os, const point &p) {
    os << p.x << ", " << p.y;
    return os;
}


void main_(int n){
    vector< point > points(n);
    for(auto &p: points) cin>>p.x>>p.y;
    for(auto &p: points) p.x *= 2, p.y *= 2;

    sort(all(points));
    auto check_symmetry = [&](point a, point v) {

        vector<point> projections;
        for(auto p: points) {
            if(point_in_line(a, v, p)) {
                projections.push_back(p);
                continue;
            }

            point u = p-a;
            lli num = 2 * u.dot(v);
            lli den = v.dot(v);
            if((num * v.x) % den || (num * v.y) % den) {
                return false;
            }
            point p_proj = (v * num) / den - u + a;

            projections.push_back(p_proj);
        }

        sort(all(projections));
        return points == projections;
    };

    vector< pair<point, point> > candidates;
    for(int i = 0; i < 2; i++){
        point fixed = points[i];
        for(auto p: points) {
            if(p == fixed) continue;

            point middle = (fixed + p) / 2;
            point dir = (p - fixed).perp();
            candidates.push_back({middle, dir});
        }
    }

    candidates.push_back({ points[0], points[1] - points[0] });

    for(auto [a, v]: candidates){
        // cout << a << " --- " << v << endl;
        if(check_symmetry(a, v)){
            cout << "Y" << endl;
            return;
        }
    }
    cout << "N" << endl;
}

int main () {
	fastIO();


	while(true) {
		int n; cin>>n;
        if(n == -1) break;
        main_(n);
	}

	return 0;
}

