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
    Point(): x(0), y(0) {}
    Point(lli x, lli y): x(x), y(y) {}
    Point operator+(const Point & P) const{return Point(x + P.x, y + P.y);}
	Point operator-(const Point & P) const{return Point(x - P.x, y - P.y);}
    bool operator<(const Point & P) const{return x < P.x || (x == P.x && y < P.y); }
    bool operator==(const Point &P) const{return x == P.x && y == P.y;}
    bool operator!=(const Point &P) const{return !(*this == P);}
    lli dot(const Point &P) const{return x*P.x + y*P.y;}
    lli cross(const Point &P) const{return x*P.y - y*P.x;}
};


vector<Point> convexHull(vector<Point> P){
	sort(all(P));
	vector<Point> L, U;
	for(int i = 0; i < SZ(P); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]) < 0 ){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = SZ(P) - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]) < 0){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

lli area(Point A, Point B, Point C)
{
    return ((B - A).cross(C - B)); //area*2
}

void solve (int t) {
    lli n; cin>>n;
    vector<Point> points(n);
    for(int i = 0; i<n; i++)
        cin>> points[i].x >> points[i].y;
    
    vector<Point> CH = convexHull(points);
    n = SZ(CH);

    lli ans = 0;
    if(n == 3)
    {
        lli areaTriangle = abs(area(CH[0], CH[1], CH[2]));
        for(auto p: points)
        {
            if(p != CH[0] && p != CH[1] && p != CH[2])
            {
                lli areaR1 = abs(area( p, CH[1], CH[2] ));
                lli areaR2 = abs(area( CH[0], p, CH[2] ));
                lli areaR3 = abs(area( CH[0], CH[1], p ));
                ans = max(ans, areaTriangle - min({areaR1, areaR2, areaR3}));
            }  
        }
        cerr << "me lleva toda la v\n";
    }
    else
    {
        for(int i = 0; i<n; i++)
        {
            for(int left = (i+1)%n, j = (i+2)%n, right = (i+3)%n; (j+1)%n != i; j = (j+1)%n)
            {
                while( area(CH[i], CH[left], CH[j]) <
                       area(CH[i], CH[(left+1)%n], CH[j]) ) 
                    left = (left+1)%n;
                while( area(CH[i], CH[j], CH[right]) <
                       area(CH[i], CH[j], CH[(right+1)%n] ))
                    right = (right+1) %n;
                ans = max(ans, area(CH[i], CH[left], CH[j]) + area(CH[i], CH[j], CH[right]) );
            }
        }
    }
    if(ans % 2 == 0) cout << ans/2 << endl;
    else cout << ans/2 << ".5" << endl;
}

int main(){
    fastIO();
    int t; cin>>t;
    for(int i = 1; i<=t; i++){
        solve(i);
    } 
    return 0;
}