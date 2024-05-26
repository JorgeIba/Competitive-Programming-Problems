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

	point operator+=(const point & p){*this = *this + p; return *this;}
	point operator-=(const point & p){*this = *this - p; return *this;}
	point operator*=(const ld & p){*this = *this * p; return *this;}
	point operator/=(const ld & p){*this = *this / p; return *this;}


	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator>(const point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}


const int RED = 0, BLUE = 1;

bool isLeft(point p_start, point p_end, point p_test) {
    lli cross = (p_end - p_start).cross(p_test - p_start);
    if(cross > 0) return true;
    return false;
}


struct PointInfo{
    point p;
    int type;
    int ori;

    PointInfo() {}
    PointInfo(point p, int type, int ori = true): p(p), type(type), ori(ori) {}
};

void polarSort(vector<PointInfo> & P, const point & o, const point & v){
	//sort points in P around o, taking the direction of v as first angle
	sort(P.begin(), P.end(), [&](const PointInfo & xa, const PointInfo & xb){
        auto a = xa.p;
        auto b = xb.p;
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}



const point dir_v(1, 0);

void solve(){
    int n, m; cin>>n>>m;

    vector< PointInfo > points(n+m);
    for(int i = 0; i < n; i++){
        int x, y; cin>>x>>y;
        points[i] = {point(x, y), RED};
    }

    for(int i = n; i < n+m; i++){
        int x, y; cin>>x>>y;
        points[i] = {point(x, y), BLUE};
    }

    int N = n+m;


    auto get_ans = [&](array<int,2> left, int type_origin, int type_end) {
        int ans = 1e9;

        array<int, 2> right = {0, 0};
        array<int, 2> middle = {0, 0};
        middle[type_origin]++;
        middle[type_end]++;

        right[RED] = n - left[RED] - middle[RED];
        right[BLUE] = m - left[BLUE] - middle[BLUE];

        // Primero blue - left and red - right
        ans = min(ans, left[RED] + right[BLUE]);
        // luego red - left and blue - right
        ans = min(ans, left[BLUE] + right[RED]);        
        return ans;
    };

    int ans = 1e9;

    for(int i = 0; i < N; i++) {
        auto [p_i, type_i, or_i] = points[i];

        vector< PointInfo > centered_points;
        for(int j = 0; j < N; j++) {
            if(i == j)  continue;

            auto [p_j, type_j, or_j] = points[j];

            PointInfo p_mod( p_j - p_i, type_j, or_j );

            if(p_mod.p.y < 0) {
                p_mod.p.y = -p_mod.p.y;
                p_mod.p.x = -p_mod.p.x;
                p_mod.ori = false;
            }

            centered_points.push_back(p_mod);
        }

        
        polarSort(centered_points, point(0, 0), dir_v);


        array<int, 2> left = {0, 0};

        int M = SZ(centered_points);
        for(int j = 0; j < M; j++) {
            auto [p_j, type_j, or_j] = centered_points[j];
            if(or_j) {
                left[type_j]++;
            }
        }


        for(int j = 0; j < M; j++) {
            auto [p_j, type_j, or_j] = centered_points[j];

            if(or_j) {
                left[type_j]--;
            }

            ans = min(ans, get_ans(left, type_i, type_j));

            if(!or_j) {
                left[type_j]++;
            }
        }


    }

    cout << ans << endl;
}




int main () {
	//fastIO();
    
    int t; cin>>t;
    while(t--) solve();


	return 0;
}

