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
    ld x, y, z;
    ld f;

    point(): x(0), y(0), z(0), f(0) {}
    point(ld x, ld y, ld z, ld f = 1): x(x), y(y), z(z), f(f) {}

    ld norm() const {
        return sqrtl(x*x+y*y+z*z);
    }
    point unit() const {
        ld len = norm();
        // debugg(len);
        return {x / len, y / len, z / len};
    }

    ld dot(const point &p) const {
        return x*p.x + y*p.y + z*p.z;
    }

    point operator*(const ld &k) const {
        return {k*x, k*y, k*z, f};
    }

    point operator+(const point &p) const {
        return {x+p.x, y+p.y, z+p.z, f};
    }

    point operator-(const point &p) const {
        return {x-p.x, y-p.y, z-p.z, f};
    }
};

ostream &operator<<(ostream &os, const point &p) {
    os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
    return os;
}



const ld eps = 1e-7;
const ld INF = 1e17;

vector< point > v_dirs = {
    {1, 1, 1},
    {1, -1, 1},
    {-1, 1, 1},
    {-1, -1, 1},
};

void main_(int test){

    int n; cin>>n;

    vector< point > points(n);
    forn(i, n) {
        int x, y, z, f; cin>>x>>y>>z>>f;
        points[i] = point(x, y, z, f);
    }


    ld l = 0, r = 1e9;
    while(r-l > eps){
        ld mid = (l+r)/2;
        bool ok = true;

        for(auto dir: v_dirs) {

            ld left = -INF, right = INF;
            for(auto p: points) {
                point up = p + dir * p.f * (mid/3);
                point down = p - dir* p.f * (mid/3);

                // cout << up << " --- " << down << " === " << down.dot(dir) << " and " << up.dot(dir) << " with dir: " << dir << endl;

                left = max(left, down.dot(dir));
                right = min(right, up.dot(dir));
            }

            if(left > right){
                ok = false;
                break;
            } 
        }

        // debugg(ok);
        if(ok){
            // cout << mid << endl;
            r = mid;
        } 
        else l = mid;
    }
    

    cout << "Case #" << test << ": " << fixed << setprecision(10) << r << endl;



}

int main () {
	fastIO();

	int t = 1; 
	cin>>t;

	forr(i, 1, t){
		main_(i);
	}

	return 0;
}

