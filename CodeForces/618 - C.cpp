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
    lli x, y, idx;
    Point() {}
    Point(lli x, lli y): x(x), y(y) {}

    lli cross(const Point &P){ return x*P.y - y*P.x; } 

    Point operator-(const Point &P) {return {x-P.x, y-P.y}; }

    bool operator<(const Point &P){ return (x==P.x && y<P.y) ||  (x < P.x ); }
};


int main () {
	//fastIO();
    lli n; cin>>n;
    vector<Point> points(n);
    for(int i = 0; i<n; i++)
    {
        cin>>points[i].x>>points[i].y;
        points[i].idx = i+1;
    }

    sort(all(points));
    Point A = points[0];
    Point B = points[1];

    for(int i = 2; i<n; i++)
    {
        if( abs((A-B).cross(points[i]-B)) > 0 )
        {
            cout << A.idx << " " << B.idx << " " << points[i].idx << endl;
            return 0;
        }
    }

	return 0;
}