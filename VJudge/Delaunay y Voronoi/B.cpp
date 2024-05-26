#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

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
	double x, y;
	int idx;
	point(): x(0), y(0), idx(-1) {}
	point(double x, double y): x(x), y(y), idx(-1) {}
	
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	double dot(const point & p) const{return x * p.x + y * p.y;}
	double cross(const point & p) const{return x * p.y - y * p.x;}
	double norm() const{return x * x + y * y;}
	double length() const{return sqrtl(x*x + y*y);}
};


vector< vector<point> > delaunay(const vector<point> &p) {
	int n = SZ(p);
	vector<double> z(n);
	vector< vector<point> > ret;
	for (int i = 0; i < n; i++)
		z[i] = p[i].norm();
	for (int i = 0; i < n-2; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = i+1; k < n; k++) {
				if (j == k) continue;
				double xn = (p[j].y - p[i].y)*(z[k]-z[i]) - (p[k].y - p[i].y) * (z[j]-z[i]);
				double yn = (p[k].x - p[i].x)*(z[j]-z[i]) - (p[j].x - p[i].x) * (z[k]-z[i]);
				double zn = (p[j].x - p[i].x)*(p[k].y - p[i].y) - (p[k].x - p[i].x)*(p[j].y - p[i].y);
				bool flag = zn < 0;
				for (int m = 0; flag && m < n; m++)
					flag = flag && ((p[m].x - p[i].x)*xn +
					(p[m].y - p[i].y)*yn +
					(z[m]-z[i])*zn <= 0);
				vector< point > aux(3);
				aux[0] = p[i];
				aux[1] = p[j];
				aux[2] = p[k];
				if (flag) ret.push_back(aux);
			}
		}
	}
	return ret;
}

const double pi = acos(-1);

void main_(int n){

    vector< point > points(n);
    for(int i = 0; i < SZ(points); i++){
        int x, y; cin>>x>>y;
        points[i].x = x;
        points[i].y = y;
    }
    
    vector< vector<point> > triangles = delaunay(points);

    double ans = pi;
    for(int j = 0; j < SZ(triangles); j++){
        vector<point> triang = triangles[j];
        for(int i = 0; i < 3; i++){
            point prevv = triang[(i-1+3)%3];
            point curr  = triang[i];
            point nextt = triang[(i+1)%3];

            point a = (nextt - curr);
            point b = (prevv - curr);
            double ang = acos(a.dot(b) / (a.length() * b.length()));
            if(ang > pi) ang -= pi;

            // debugg(ang * 180 / pi);
            ans = min(ans, ang);
        }
    }
    cout << fixed << setprecision(2) << ans * 180 / pi << endl;
}


int main () {
	fastIO();
	
	int n;
    while(cin>>n){
        main_(n);
    }


	return 0;
}

