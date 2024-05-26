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

const lli eps = 0, pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(lli a, lli b){return a-b >= -eps;}     //a >= b
bool leq(lli a, lli b){return b-a >= -eps;}     //a <= b
bool ge(lli a, lli b){return a-b > eps;}        //a > b
bool le(lli a, lli b){return b-a > eps;}        //a < b
bool eq(lli a, lli b){return abs(a-b) <= eps;}  //a == b

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

void polarSort(vector<point> & P, const point & o, const point & v){
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}

vector<point> convexHull(vector<point> P){
	sort(P.begin(), P.end());
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

bool crossesRay(const point & a, const point & b, const point & p){
	return (geq(b.y, p.y) - geq(a.y, p.y)) * sgn((a - p).cross(b - p)) > 0;
}

int pointInPolygon(const vector<point> & P, const point & p){
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	}
	return rays & 1;
}

void main_(){

    int n; cin>>n;
    vector< point > points(n);
    for(auto &p: points) cin>>p.x>>p.y;

    if(n == 1 || n == 2){
        cout << 0 << endl;
        return;
    }
    point origin(0,0);

    auto CH = convexHull(points);
    if(pointInPolygon(CH, origin) == 0) {
        cout << 0 << endl;
        return;
    }

    polarSort(points, origin, point(1, 0));

    int ans = n;
    for(int i = 0, j = 1, total_j = 1; i < n; i++){
        if(i == j){
            j++;
            total_j++;
        }
            
        point pi = points[i], pj = points[j];

        while((pj - pi).cross(origin - pi) > 0 && j != i){
            total_j++;
            j = (j+1) % n;
            pj = points[j];
        }

        if((pj-pi).cross(origin-pi) == 0) continue;

        ans = min(ans, total_j - i + 1);
    }

    cout << ans-2 << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

