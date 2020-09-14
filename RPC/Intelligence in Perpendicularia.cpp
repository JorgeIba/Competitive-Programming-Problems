#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define point pair<lli,lli>
#define x first
#define y second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli INF = 1e18;

int main () {
	//fastIO();
    lli n; cin>>n;
    vector< point > points(n);
    lli totalPerimeter = 0;
    point last;
    lli max_x = -INF, min_x = INF, max_y = -INF, min_y = INF;
    for(int i = 0; i<n; i++)
    {
        cin>>points[i].x>>points[i].y;        
    }

    for(int i = 0; i<n; i++)
    {
        if(points[i].x == points[(i+1)%n].x )
        {
            totalPerimeter += abs(points[i].y - points[(i+1)%n].y);
        }
        else
        {
            totalPerimeter += abs(points[i].x - points[(i+1)%n].x) ;
        }
        //cout << "[" << points[i].x << ", " << points[i].y << "]   ->   " << "[" << points[(i+1)%n].x << ", " << points[(i+1)%n].y << "]\n";
        max_x = max(max_x, points[i].x);
        min_x = min(min_x, points[i].x);
        max_y = max(max_y, points[i].y);
        min_y = min(min_y, points[i].y);
    }
    lli perimeter = 2*(max_x - min_x) + 2*(max_y - min_y);
    //cout << totalPerimeter << " " << perimeter << endl;
    cout << (totalPerimeter - perimeter) << endl;

	return 0;
}