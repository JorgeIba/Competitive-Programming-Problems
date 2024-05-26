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


const ld eps = 1e-15;
struct Point{
    ld x, y;
    Point(): x(0), y(0) {}
    Point(ld x, ld y): x(x), y(y){}

    Point operator-(const Point &P) const {
        return {x - P.x, y - P.y};
    }

    Point operator+(const Point &P) const {
        return {x + P.x, y + P.y};
    }

    Point operator*(const ld k) const {
        return {x * k, y * k};
    }

    ld cross(const Point &P) const {
        return x * P.y - y * P.x;
    }
};



Point intersectLines(const Point & a1, const Point & v1, const Point & a2, const Point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}


int main () {
	//fastIO();
	
    ld B, b, h; cin>>B>>b>>h;

    vector< Point > trapez(4);
    trapez[0] = {0, h};
    trapez[1] = {0, 0};
    trapez[2] = {B, 0};
    trapez[3] = {b, h};

    auto get_diff = [&](Point p){
        vector<ld> areas;
        for(int i = 0; i < 4; i++){
            ld area = trapez[i].cross(trapez[(i+1)%4]) + trapez[(i+1)%4].cross(p) + p.cross(trapez[i]);
            areas.push_back(abs(area)/2);
        }

        return *max_element(all(areas)) - *min_element(all(areas));
    };

    auto f_2 = [&](ld y) -> ld {
        auto pt = intersectLines(Point(0, y), Point(1, 0), trapez[3], trapez[2] - trapez[3]);
        ld l = 0, r = pt.x;
        // debugg(l);
        // debugg(r);
        while(r-l > eps){
            ld l_1 = l + (r-l)/3;
            ld fl = get_diff(Point(l_1, y));

            ld r_1 = r - (r-l)/3;
            ld fr = get_diff(Point(r_1, y));

            if(fl < fr){
                r = r_1;
            } else {
                l = l_1;
            }
        }

        return l;
    };

    auto f_1 = [&]() -> Point {
        ld l = 0, r = h;
        while(r-l > eps) {
            ld l_1 = l + (r-l)/3;
            ld fl = f_2(l_1);

            ld r_1 = r - (r-l)/3;
            ld fr = f_2(r_1);

            if(get_diff({fl, l_1}) < get_diff({fr, r_1})){
                r = r_1;
            } else {
                l = l_1;
            }
        }
        return {f_2(l), l};
    };

    // auto p_ans = f_2(6);
    // cout << p_ans << endl;

    auto p_ans = f_1();

    cout <<fixed << setprecision(20) <<  get_diff(p_ans) << endl;

    // cout << get_diff(p_ans) << endl;
    // debugg(p_ans);
    
    // debugg(p_ans.x);
    // debugg(p_ans.y);
    


	return 0;
}

