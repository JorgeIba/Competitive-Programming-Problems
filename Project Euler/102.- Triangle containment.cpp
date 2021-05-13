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
    ld x, y;
    Point() {}
    Point(ld x, ld y): x(x), y(y) {}

    ld cross(const Point &P) {return x*P.y - y*P.x;}

    Point operator-(const Point &P) { return {x-P.x, y-P.y}; }

    bool operator<(const Point &P){ return x < P.x || (x == P.x && y < P.y); }
};

lli sign(ld num)
{
    if(num < 0) return -1;
    else if(num == 0) return 0;
    return 1;
}

Point origin(0,0);

bool is_inside(vector<Point> points)
{
    vector< lli > signs(3);
    for(int i = 0; i<3; i++)
    {
        signs[i] = sign((points[(i+1)%3] - points[i]).cross(origin - points[i]));
    }
    for(int i = 0; i<3; i++)
    {
        if(signs[i] != signs[(i+1)%3]) return false;
    }
    return true;
}


int main () {
	//fastIO();
    ld x1, y1, x2, y2, x3, y3;
    lli ans = 0;
    while (cin>>x1>>y1>>x2>>y2>>x3>>y3)
    {
        vector<Point> points = {{x1, y1}, {x2, y2}, {x3, y3}};
        sort(all(points));

        if(is_inside(points)) ans++;
    }
    cout << ans << endl;
    
	return 0;
}