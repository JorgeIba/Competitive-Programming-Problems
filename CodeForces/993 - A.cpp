#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ldd long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

struct Point{
    ldd x, y;
    Point() {}
    Point(lli x, lli y): x(x), y(y) {}

    Point operator-(const Point &P) { return {x-P.x, y-P.y}; }
    ldd cross(const Point &P) { return x*P.y - y*P.x; }
    ldd dot(const Point &P){ return x*P.x + y*P.y;}
};

const lli INF = 1e9;

struct Square{
    Point v1, v2, v3, v4, center;
    vector<Point> vertex;
    bool diagonal;

    Square() {}
    Square(Point v1, Point v2, Point v3, Point v4): v1(v1), v2(v2), v3(v3), v4(v4) {
        if(v1.x == v2.x || v1.y == v2.y) diagonal = false;
        else diagonal = true;
        vertex.push_back(v1);
        vertex.push_back(v2);
        vertex.push_back(v3);
        vertex.push_back(v4);

        ldd left = INF, right = -INF, up = -INF, down = INF;
        for(auto P: vertex)
        {
            left = min(left, P.x), right = max(right, P.x);
            down = min(down, P.y), up = max(up, P.y);
        }
        center = { (ldd) (left + right) / 2, (ldd)(down+up) / 2 };
    }
};

ostream &operator<<(ostream &os, const Point & p){return os << "(" << p.x << ", " << p.y << ")";}

vector<Point> get_order(Square A)
{
    Point lu, ld, ru, rd;

    ldd max_right = -INF, max_upper = -INF;
    for(auto P: A.vertex)
    {
        max_right = max(max_right, P.x);
        max_upper = max(max_upper, P.y);
    }

    for(auto P: A.vertex)
    {
        if(P.x == max_right && P.y == max_upper)
            ru = P;
        else if(P.x == max_right && P.y != max_upper)
            rd = P;
        else if(P.x != max_right && P.y == max_upper)
            lu = P;
        else
            ld = P;
    }
    return {lu, ld, ru, rd};
}

lli sign(lli n){
    if(n<0) return -1;
    else if(n == 0) return 0;
    return 1;
}

bool point_in_segment(Point A, Point B, Point P)
{
    return (B-A).cross(P-A) == 0 && (A-P).dot(B-P) <= 0;
}

bool is_inside(Square A, Point P) 
{
    Point d1 = A.v2 - A.v1, d2 = A.v3 - A.v4;
    Point e1 = A.v4 - A.v1, e2 = A.v3 - A.v2;

    lli crossd1 = (P-A.v1).cross(d1), crossd2 = (P-A.v4).cross(d2);
    lli crosse1 = (P-A.v1).cross(e1), crosse2 = (P-A.v2).cross(e2);

    for(int i = 0; i<4; i++)
        if(point_in_segment(A.vertex[(i+1)%4], A.vertex[i], P)) return true;

    if((sign(crossd1) != sign(crossd2)) && (sign(crosse1) != sign(crosse2)))
        return true;
    
    return false;
}


int main () {
	//fastIO();
    lli x1,y1, x2, y2, x3, y3, x4, y4; 
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    Square A = Square({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4});

    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    Square B = Square({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4});

    assert(A.diagonal != B.diagonal);

    bool ans = false;

    for(auto P: B.vertex)
        if(is_inside(A, P) || is_inside(A, B.center))
            ans = true;

    for(auto P: A.vertex)
        if(is_inside(B, P) || is_inside(B, A.center))
            ans = true;


    cout << ( ans? "YES" : "NO") << endl;

    
	return 0;
}