#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace __gnu_pbds;
using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}

    bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
	bool half(const point & p) const{return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) < 0);}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

lli compareDistancePointLine(const point & a, const point & v, const point & p){
	//line: a + tv, point p
	return v.cross(p - a);
}

void polarSort(vector<point> & P, const point & o, const point & v){
	//sort points in P around o, taking the direction of v as first angle
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}


const int maxN = 400+1;
int bit[maxN];
// vector< point > points(n);



//single element increment
void update(int pos, int value){
    while(pos < 2*maxN){
        bit[pos] += value;
        pos |= pos + 1;
    }
}

//range query, [0, r]
int queryPrefix(int r){
    int res = 0;
    while(r >= 0){
        res += bit[r];
        r = (r & (r + 1)) - 1;
    }
    return res;
}

//range query, [l, r]
int query(int l, int r){
    return queryPrefix(r) - queryPrefix(l - 1);
}


lli getTotalQuadrilaterals(const vector<point> &points, lli S) {
    int n = SZ(points);

    lli ansT = 0;
    for(int i = 0; i < n; i++) {
        point p1 = points[i];
        for(int j = 0; j < i; j ++) {   
            point p2 = points[j];

            auto getArea = [&](point p_cross) {
                return abs((p_cross - p1).cross(p2 - p1));
            };

            vector<point> side_1, side_2;

            for(auto &p: points){
                if(p == p1 || p == p2) continue;
                if(compareDistancePointLine(p1, (p2-p1), p) < 0) side_1.push_back(p);
                else side_2.push_back(p);
            }


            sort(all(side_2), [&](point a, point b) {
                return getArea(a) > getArea(b);
            });



            for(auto &p_side: side_1) {
                lli provisional_area = abs((p_side - p1).cross(p2 - p1));
                lli needed = 2*S - provisional_area;

                int l = 0, r = SZ(side_2)-1, ans = -1;
                if(needed > 0) {
                    while(l <= r) {
                        int mid = l + (r-l)/2;
                        point p_mid = side_2[mid];
                        if(getArea(p_mid) >= needed) {
                            ans = mid;
                            l = mid+1;
                        } else {
                            r = mid-1;
                        }
                    }
                } else {
                    ans = SZ(side_2)-1;
                }
                

                ansT += ans + 1;
            }            
        }
    }

    return ansT;
}


lli getConvexQuadrilaterals(const vector<point> &points, lli S) {
    lli n = SZ(points);

    lli ansT = 0;
    for(int i = 0; i < n; i++) {
        point p1 = points[i];
        for(int j = 0; j < i; j++) {   

            
            point p2 = points[j];

            auto getArea = [&](point p_cross) {
                return abs((p_cross - p1).cross(p2 - p1));
            };

            vector<point> side_1, side_2;

            for(auto &p: points){
                if(p == p1 || p == p2) continue;
                if(compareDistancePointLine(p1, (p2-p1), p) < 0) side_1.push_back(p);
                else side_2.push_back(p);
            }

            
            vector<lli> all_crosses;
            for(auto p_cross: side_1) all_crosses.push_back( getArea(p_cross) );
            for(auto p_cross: side_2) all_crosses.push_back( 2*S - getArea(p_cross) );;
        

            sort(all(all_crosses));
            auto getIdx = [&](lli cross) {
                return lower_bound(all(all_crosses), cross) - all_crosses.begin();
            };
        

            for(int i = 0; i <= n; i++) bit[i] = 0;
            
            polarSort(side_1, p2, p1-p2);
            polarSort(side_2, p2, p1-p2);
            reverse(all(side_1));
            reverse(all(side_2));

            int k = 0; 
            lli max_cross = 0;
            for(auto &p_side: side_2) {
                while(k < SZ(side_1) && (p2 - p_side).cross(side_1[k] - p_side) >= 0) {
                    update(getIdx( getArea(side_1[k]) ), 1);
                    max_cross = max(max_cross, getArea(side_1[k]));
                    k++;
                }
                lli need = 2*S - getArea(p_side);
                int ans_for_p_side = need <= 0 ? k : ( max_cross < need ? 0 : query(getIdx(need), n+1) );
                ansT += ans_for_p_side;
            }

            polarSort(side_1, p1, p2-p1);
            polarSort(side_2, p1, p2-p1);
            
            for(int i = 0; i <= n; i++) bit[i] = 0;

            k = 0, max_cross = 0; 
            for(auto &p_side: side_2) {
                while(k < SZ(side_1) && (side_1[k] - p_side).cross(p1 - p_side) >= 0) {
                    update(getIdx( getArea(side_1[k]) ), 1);
                    max_cross = max(max_cross, getArea(side_1[k]));
                    k++;
                }

                lli need = 2*S - getArea(p_side);
                int ans_for_p_side = need <= 0 ? k : ( max_cross < need ? 0 : query(getIdx(need), n+1) );
                ansT += ans_for_p_side;
            }
        }
    }

    return ansT;
}



int main () {
	fastIO();

    
    lli S;
    int n; cin>>S>>n;
    time_t begin = clock();

    
    vector<point> points(n);
    for(auto &x: points) cin>>x;


    lli totalQuadrilaterals = getTotalQuadrilaterals(points, S);

    

    lli convexQuadrilaterals = getConvexQuadrilaterals(points, S);
    cout << (double)(clock() - begin)/CLOCKS_PER_SEC << endl;

    cout << (totalQuadrilaterals + convexQuadrilaterals) / 2 << endl;


	return 0;
}
