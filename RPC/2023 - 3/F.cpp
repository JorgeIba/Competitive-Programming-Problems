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

const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	point operator+=(const point & p){*this = *this + p; return *this;}
	point operator-=(const point & p){*this = *this - p; return *this;}
	point operator*=(const ld & p){*this = *this * p; return *this;}
	point operator/=(const ld & p){*this = *this / p; return *this;}

	point rotate(const ld & a) const{return point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a));}
	point perp() const{return point(-y, x);}
	ld ang() const{
		ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
	}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	ld norm() const{return x * x + y * y;}
	ld length() const{return sqrtl(x * x + y * y);}
	point unit() const{return (*this) / length();}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator>(const point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return eq((p - a).cross(v), 0);
}

bool pointInSegment(const point & a, const point & b, const point & p){
	//segment ab, point p
	return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
}



int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
	//segment ab, segment cd
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no point
			}
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
	}
}



vector<point> convexHull(vector<point> P){
	sort(P.begin(), P.end());
	vector<point> L, U;
	for(int i = 0; i < SZ(P); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}




typedef pair<lli,ld> pairi;
const int MAXN = 510;
vector< pairi > adjList[MAXN + 10];

const lli INF = 1e17;
vector<ld> dijkstra(int start){   
    int n = MAXN;
    vector<ld> dist( n, INF );

    priority_queue< pair<ld,int> , vector<pair<ld,int>>, greater<pair<ld,int>> > pq;

    pq.push({0,start}); // {costo, nodo}
    dist[start] = 0;

    while(!pq.empty()){
        auto [dist_u, u] = pq.top(); pq.pop();
        
        if(dist_u > dist[u]) continue;

        for(auto [v, w]: adjList[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
    return dist;
}




int main () {
	//fastIO();

    int n; cin>>n;
    vector< vector<point> > clouds(n);

    point start, end;
    cin>>start.x>>start.y>>end.x>>end.y;


    forn(i, n) {
        int m; cin>>m;
        vector< point > points(m);
        for(auto &p: points) cin>>p.x>>p.y;

        clouds[i] = convexHull(points);
    }

    map< pair<int,int>, int > to_map;
    int timee = 0;

    auto mapping = [&](point p) {
        int x = p.x, y = p.y;
        if(!to_map.count({x, y})) {
            to_map[{x, y}] = timee++;
        }
        return to_map[{x, y}];
    };

    map< point, int > poly_belongs;

    vector< pair<point,point> > segments;
    vector< point > all_points;
    for(int i = 0; i < n; i++) {
        auto cloud = clouds[i];
        int m = SZ(cloud);
        for(int j = 0; j < m; j++) {
            poly_belongs[ cloud[j] ] = i;

            segments.push_back( {cloud[j], cloud[(j+1) % m]} );
            all_points.push_back(cloud[j]);
        }
    }


    poly_belongs[start] = -1;
    poly_belongs[end] = -2;

    all_points.push_back(start);
    all_points.push_back(end);


    auto add_edges = [&](point p) {
        for(int j = 0; j < SZ(all_points); j++) {
            point p_1 = all_points[j];
            if(p_1 == p) continue;

            if(poly_belongs[p] == poly_belongs[p_1]) continue;


            bool is_valid = true;
            for(auto [a, b]: segments) {
                if(intersectSegmentsInfo(p, p_1, a, b) == 1 && p != a && p != b && p_1 != a && p_1 != b) {
                    is_valid = false;
                    break;
                }
            }

            if(is_valid) {
                ld dist = (p - p_1).length();
                // cout << p << " ---> " << p_1 << endl;
                adjList[ mapping(p)    ].push_back( {mapping(p_1), dist }  );
                adjList[ mapping(p_1)  ].push_back( {mapping(p), dist }  );
            }
        }
    };



    for(int i = 0; i < n; i++) {
        auto cloud = clouds[i];
        int m = SZ(cloud);
        for(int j = 0; j < m; j++) {
            auto p_1 = cloud[j];
            auto p_2 = cloud[(j+1) % m];

            ld dist = (p_1- p_2).length();

            adjList[ mapping(p_1)  ].push_back( {mapping(p_2), dist }  );
            adjList[ mapping(p_2)  ].push_back( {mapping(p_1), dist }  );

        }
    }


    for(int i = 0; i < SZ(all_points); i++) {
        auto p = all_points[i];
        add_edges(p);
    }

    auto dist = dijkstra(mapping(start));

    cout << fixed << setprecision(10) << dist[ mapping(end) ] << endl;
	

	return 0;
}

