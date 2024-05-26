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

const ld pi = acos(-1);
struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}


	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
    ld length() const{return sqrtl(x * x + y * y);}

	bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
};


int main () {
	fastIO();
    int n, s; cin>>n>>s;

    vector< point > points(n);
    for(auto &p: points) cin>>p.x>>p.y;


    auto get_angle = [](ld rad){
        return rad * 180 / pi;
    };

    vector<ld> angles;
    for(int i = 0; i < n; i++){
        point p_1 = points[(i-1+n)%n] - points[i];
        point p_2 = points[(i+1)%n] - points[i];
        

        ld angle = acosl( (ld) p_1.dot(p_2) / (p_1.length() * p_2.length()) );

        angles.push_back(get_angle(angle));
        // cout << get_angle(angle) << endl;   
    }

    const ld eps = 1e-16;
    auto can = [&](ld target){
        lli needs = 0;
        for(auto alpha: angles){
            if(alpha >= target) continue;
            lli cnt = ceil( (target - alpha) / (180-target) );

            needs += cnt;
        }

        return needs <= s;
    };

    ld l = 0, r = 180-eps;

    forn(i, 300){
        ld mid = (l+r)/2;
        if(can(mid)) l = mid;
        else r = mid;
    }

    cout << fixed << setprecision(15);
    cout << 360 - l << endl;

	return 0;
}


// def f(alpha):
//     if(alpha >= limit) return 0
    
//     return 1 + f(alpha + 180 - target)

// def f(alpha):
//     cnt = 0
//     while(alpha < target):
//         cnt++;
//         alpha = alpha + 180 - target

// def f(alpha):
//     cnt = 0
//     alpha + cnt*(180 - target) >= limit
//     cnt >= (limit - alpha) / (180 - target)
//     5 >= 6.5
//     5 >= 7

// def f(alpha):
//     cnt = 0
//     alpha + cnt*(180 - target) >= limit
//     cnt >= (limit - alpha) / (180 - target)
