#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

struct Point{
    lli x, y;
    Point() {}
    Point(lli x, lli y): x(x), y(y) {}

    Point operator-(const Point &P) { return {x-P.x, y-P.y}; }
    bool operator==(const Point &P) { return x == P.x && y == P.y; }
    bool operator!=(const Point &P) {return !(*this == P); }

    lli cross(const Point &P) { return x*P.y - y*P.x; }
};

lli n;
vector<Point> points;

bool check(Point A, Point B)
{
    vector<Point> nel;
    for(int i = 0; i<n; i++)
    {
        if( points[i] != A && points[i] != B && (A-B).cross(points[i] - B) != 0 ) nel.push_back(points[i]);
    }

    /*
    cout << A.x << " - " << A.y << "  " << B.x << " - " << B.y << endl;
    for(auto C: nel) cout << C.x << " " << C.y << endl;
    cout << endl;
    */

    for(int i = 2; i < SZ(nel); i++){
        if( (nel[i-2] - nel[i-1]).cross(nel[i] - nel[i-1]) != 0) return false;
    }
    return true;
}


int main () {
	fastIO();
    cin>>n;
    points.resize(n);
    for(int i = 0; i<n; i++)
    {
        cin>>points[i].x>>points[i].y;
    }

    if(n<=4){
        cout << "YES\n";
        return 0;
    }

    Point A = points[0], B = points[1], C = points[2];

    //cout << check(A, B) << " " << check(A, C) << " " << check(B, C) << endl;
    bool ans = false;
    if( check(A, B) || check(A, C) || check(B, C) )
        ans = true;

    cout << (ans? "YES" : "NO") << endl;
    
    
	return 0;
}