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
 
struct Point
{
    lli x, y, z;
    Point() {}
    Point(lli x, lli y, lli z=0): x(x), y(y), z(z) {}
 
    vector<Point> getVertex()
    {
        return {{x-z, y-z},
                {x-z, y+z},
                {x+z, y-z}, 
                {x+z, y+z}};
    }
};
 
const lli INF = 1e18;
 
int main () {
	fastIO();
    lli n; cin>>n;
    vector< Point > points, obe;
    for(int i = 0; i<n; i++)
    {
        lli x, y, z; cin>>x>>y>>z;
        Point obelisk(x,y,z);
		obe.push_back(obelisk);
        auto vertex = obelisk.getVertex();
        points.insert(points.end(), all(vertex));
    }
 
    //for(auto p: points) cout << p.x << " " << p.y << endl;
 
    lli l = INF, r = -INF, d = INF, u = -INF;
    
    for(auto p: points)
    {
        l = min(l, p.x), r = max(r, p.x);
        d = min(d, p.y), u = max(u, p.y);
    }
 
    lli side = max(r-l, u-d);
    if(side == (r-l)){
		int diff = (r-l) - (u-d);
		d -= diff;
    }
    else{
		int diff = (u-d) - (r-l);
		l -= diff;
    }

	/* assert((r-l) == (u-d)); */
 
	if(side & 1){
		r++;
		u++;
		side++;
	}
 
    lli half_x = (r + l)/2;
    lli half_y = (u + d)/2;
	lli h = side / 2;
	for(auto p:obe){
		lli d = max(abs(half_x-p.x), abs(half_y-p.y));
		assert(p.z <= h-d);
	}
 
    cout << half_x << " " << half_y << " " << h << endl;
    
	return 0;
}
