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

    lli cross(const Point &R) const {
        return x * R.y - y * R.x;
    }

    Point operator-(const Point &R) const {
        return {x - R.x, y - R.y};
    }
    
};


const int UP = 0;
const int DOWN = 1;

int main () {
	//fastIO();

    int n; cin>>n;

    vector< Point > P(n);
    for(auto &p: P) cin>>p.x>>p.y;


    int start = 0;
    for(int i = 0; i < n; i++){
        Point p_1 = P[i], p_2 = P[(i+1)%n];
        Point edge = p_2 - p_1;
        if(edge.y != 0) start = i;
    }

    vector< pair<Point, int> > edges;
    for(int i = start, j = 0; j < n; j++, i = (i+1)%n){
        Point p_1 = P[i], p_2 = P[(i+1)%n];
        Point edge = p_2 - p_1;
        if(edge.y > 0){
            edges.push_back({edge, UP});
        } else if(edge.y < 0){
            edges.push_back({edge, DOWN});
        } else {
            edges.push_back({edge, edges.back().second});
        }
    }


    int ans = 0;
    for(int i = 0; i < n; i++){
        auto [edge_1, t_1] = edges[i];
        auto [edge_2, t_2] = edges[(i+1)%n];
        if(t_1 == DOWN && t_2 == UP && edge_1.cross(edge_2) > 0){
            ans++;
        }
    }

    cout << ans << endl;


	return 0;
}

