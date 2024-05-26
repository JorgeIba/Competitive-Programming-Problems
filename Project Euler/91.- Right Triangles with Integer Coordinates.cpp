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


struct Point{
    lli x, y; 
    Point(): x(0), y(0) {}
    Point(lli x, lli y): x(x), y(y) {}

    lli dot(const Point &P) const {
        return x * P.x + y * P.y;
    };

    lli cross(const Point &P) const {
        return x * P.y - y * P.x;
    }

    Point operator-(const Point &P) const {
        return {x - P.x, y - P.y};
    }

    bool operator<(const Point &P) const {
        return pair<lli,lli>{x, y} < pair<lli,lli>{P.x, P.y};
    }
};


int main () {
	//fastIO();
	
	const int limit = 50;
    int ans = 0;

    Point O(0, 0);
    forr(x_1, 0, limit){
        forr(y_1, 0, limit){
            forr(x_2, 0, limit){
                forr(y_2, 0, limit) {
                    vector<Point> triangle;
                    triangle.push_back(O);
                    Point p1(x_1, y_1);
                    Point p2(x_2, y_2);

                    if((p1 - O).cross(p2 - O) == 0) continue;

                    bool angle_1 = (p1 - O).dot(p2 - O) == 0;
                    bool angle_2 = (O - p2).dot(p1 - p2) == 0;
                    bool angle_3 = (O - p1).dot(p2 - p1) == 0;

                    ans += (angle_1 || angle_2 || angle_3);

                    // else if((p1 - O).cross(p2 - O) > 0)  {
                    //     triangle.push_back(p1);
                    //     triangle.push_back(p2);
                    // }
                    // else if((p1 - O).cross(p2 - O) < 0) {
                    //     triangle.push_back(p2);
                    //     triangle.push_back(p1);
                    // }
                }
            }
        }
    }

    cout << ans << " " << ans/2 << endl;


	return 0;
}

